#include "Monster.h"
#include "audio/include/AudioEngine.h"

void Monster::UpdateMonster(float dt)
{
	//实时更新怪物坐标
	m_x = monster->getPosition().x;
	m_y = monster->getPosition().y;
	CCLOG("m_x=%f, m_y=%f", m_x, m_y);
	//判断是否死亡
	if (isDead())
	{
		DeadAnimate();
		scheduleOnce([this](float dt)
			{
				this->RemoveMonster();;
			}, 0.35f, "remove_monster");
	}
	// 判断是否碰到萝卜
	Rect monsterRect = monster->getBoundingBox();
	Rect carrotRect = carrot->getBoundingBox();
	if (monsterRect.intersectsRect(carrotRect)) {
		carrot->hp -= m_attack;
		cocos2d::AudioEngine::play2d("monster/Bite.mp3");
		this->RemoveMonster();
	}
}

void Monster::GetHurt(float damage)
{
	c_blood -= damage;//当前血量减去伤害
	if (c_blood < 0)
	{
		c_blood = 0;
	}
	blood->setPercent(float(c_blood) / m_blood * 100);//更新血条
}

MoveBy* Monster::CreateAction(Path path)
{
	//生成动作
	MoveBy* moveAction;
	switch (path.dir)
	{
	case 'r':
		moveAction = MoveBy::create(path.distance / m_speed, Vec2(path.distance, 0));
		break;
	case 'l':
		moveAction = MoveBy::create(path.distance / m_speed, Vec2(-path.distance, 0));
		break;
	case 'u':
		moveAction = MoveBy::create(path.distance / m_speed, Vec2(0, path.distance));
		break;
	case 'd':
		moveAction = MoveBy::create(path.distance / m_speed, Vec2(0, -path.distance));
		break;
	default:
		moveAction = MoveBy::create(0, Vec2(0, 0));
	}
	return moveAction;
}

void Monster::Move(const std::vector<Path>& path,float dt)
{
	Vector <FiniteTimeAction*> vec;
	//延时出现
	auto delay = DelayTime::create(dt);
	vec.pushBack(delay);
	scheduleOnce([this](float st)
		{
			Emerge();
		}, dt, "monsterEmerge");
	monster->setOpacity(0);
	blood->setOpacity(0);
	auto in = FadeIn::create(0.1f);
	vec.pushBack(in);
	for (const auto& p : path)
	{
		auto moveAction = CreateAction(p);
		vec.pushBack(moveAction);
	}
	CallFunc* remove = CallFunc::create([this]()
		{
			this->RemoveMonster();
		});
	vec.pushBack(remove);
	Sequence* sequence = Sequence::create(vec);
	monster->runAction(sequence);
	blood->runAction(sequence->clone());
}


bool Monster::init(const std::string& spriteName, float init_x, float init_y, float scale, int speed,int attack, int deadCost)
{
	if (!Node::init())
	{
		return false;
	}
	monster = Sprite::create(spriteName);	// 创建怪物精灵
	if (!monster)
		CCLOG("Failed to load sprite: %s", spriteName.c_str());
	else
	{
		monster->setScale(scale);		//设置怪物大小
		monster->setPosition(init_x, init_y);	//设置位置
		monster->setAnchorPoint(Vec2(0.5, 0));// 设置锚点

		m_speed = speed;	// 设置速度
		m_attack = attack;	//设置攻击力
		m_deadcost = deadCost;	// 设置金币

		this->addChild(monster, 4);		//添加到父节点
		
		blood = ui::LoadingBar::create("monster/blood.png");// 创建血条

		if (!blood)
		{
			CCLOG("Failed to load sprite: monster/blood.png");
		}
		else
		{
			
			blood->setPercent(100);	// 初始血量为100%
			blood->setPosition(Vec2(init_x, init_y + monster->getBoundingBox().size.height));	//设置位置
			blood->setAnchorPoint(Vec2(0.5, 0));		//设置锚点
			this->addChild(blood, 100);		//添加到父节点

			this->Animating();		//生成怪物动画

			//设置碰撞体
			//physicsbody = PhysicsBody::createBox(monster->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
			//PhysicsMaterial(0.1f, 1.0f, 0.0f) 是一个物理材质，包含了摩擦力、弹性系数和密度等参数。
			//这里设置了摩擦力为 0.1f，弹性系数为 1.0f，密度为 0.0f。
			//physicsbody->setDynamic(true);
			//将物体设置为动态物体，这意味着它会受到力的作用而产生运动。
			//physicsbody->setCategoryBitmask(0x01); 
			//设置物体的类别掩码。类别掩码是一个32位的整数，
			//用于标识物体所属的类别。这个值通常使用位运算来设置，以便在碰撞检测时判断物体之间的关系。
			//physicsbody->setCollisionBitmask(0x02);
			//设置物体的碰撞掩码。碰撞掩码定义了物体可以与哪些类别的物体发生碰撞。
			//physicsbody->setContactTestBitmask(0x03);
			//设置物体的接触测试掩码。接触测试掩码定义了物体可以检测哪些类别的物体。
		}
	}
	return true;
}

bool NormalMonster::init(float init_x, float init_y)
{
	if (!Node::init())
	{
		return false;
	}

	if (!Monster::init("monster/big1.png", init_x, init_y, 1.0f, NORMALSPEED, NORMALATTACK, NORMALMONEY))
	{
		return false;
	}
	return true;
}

bool BigMonster::init(float init_x, float init_y)
{
	if (!Node::init())
	{
		return false;
	}
	if (!Monster::init("monster/big1.png", init_x, init_y, 1.4f, SLOWSPEED, BIGATTACK, BIGMONEY))
	{
		return false;
	}
	return true;
}

bool FastMonster::init(float init_x, float init_y)
{
	if (!Node::init())
	{
		return false;
	}
	if (!Monster::init("monster/fast1.png", init_x, init_y, 1.0f, FASTSPEED, NORMALATTACK, NORMALMONEY))
	{
		return false;
	}
	return true;
}
