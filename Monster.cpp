#include "Monster.h"
#include "audio/include/AudioEngine.h"


static void warning(const char* filename)
{
	CCLOG("Error while loading: %s\n", filename);
}

void Monster::UpdateMonster(float dt)
{
	//实时更新怪物坐标
	m_x = monster->getPosition().x;
	m_y = monster->getPosition().y;
	CCLOG("m_x=%f, m_y=%f", m_x, m_y);
	//判断是否死亡
	if (isDead())
	{
		Dead();
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
	//当前血量减去伤害
	c_blood -= damage;
	if (c_blood < 0)
	{
		c_blood = 0;
	}
	//更新血条
	blood->setPercent(float(c_blood) / m_blood * 100);
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


bool NormalMonster::init(float init_x, float init_y)
{
	if (!Node::init())
	{
		return false;
	}

	//创建怪物精灵
	monster = Sprite::create("monster/normal1.png");
	if (!monster)
		warning("normal1.png");
	else
	{
		this->addChild(monster,4);
		//设置锚点
		monster->setAnchorPoint(Vec2(0.5,0));
		monster->setPosition(init_x, init_y);
		//设置速度
		m_speed = NORMALSPEED;
		m_attack = NORMALATTACK;
		//设置金币
		deadCost = NORMALMONEY;
		////设置碰撞体
		//physicsbody = PhysicsBody::createBox(monster->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		////PhysicsMaterial(0.1f, 1.0f, 0.0f) 是一个物理材质，包含了摩擦力、弹性系数和密度等参数。
		////这里设置了摩擦力为 0.1f，弹性系数为 1.0f，密度为 0.0f。
		//physicsbody->setDynamic(true);
		////将物体设置为动态物体，这意味着它会受到力的作用而产生运动。
		//physicsbody->setCategoryBitmask(0x01); 
		////设置物体的类别掩码。类别掩码是一个32位的整数，
		////用于标识物体所属的类别。这个值通常使用位运算来设置，以便在碰撞检测时判断物体之间的关系。
		//physicsbody->setCollisionBitmask(0x02);
		////设置物体的碰撞掩码。碰撞掩码定义了物体可以与哪些类别的物体发生碰撞。
		//physicsbody->setContactTestBitmask(0x03);
		////设置物体的接触测试掩码。接触测试掩码定义了物体可以检测哪些类别的物体。

		// 将物理体设置到怪物精灵上
		/*monster->setPhysicsBody(physicsbody);*/

		//创建血条
		blood = ui::LoadingBar::create("monster/blood.png");
		if (!blood)
		{
			warning("blood.png");
		}
		else
		{
			//初始血量为100%
			blood->setPercent(100);
			//设置血条位置
			blood->setPosition(
				Vec2(monster->getPosition().x, 
					monster->getPosition().y + monster->getBoundingBox().size.height));
			//设置锚点
			blood->setAnchorPoint(Vec2(0.5, 0));

			this->addChild(blood,100);
			this->Animating();
		}
	}
	/*schedule([this](float dt)
		{
			this->Test(dt);
		}, 1.f, "Test");*/

	return true;
}


bool BigMonster::init(float init_x, float init_y)
{
	if (!Node::init())
	{
		return false;
	}

	//创建怪物精灵
	monster = Sprite::create("monster/big1.png");
	if (!monster)
		warning("big1.png");
	else
	{
		monster->setScale(1.7f);

		this->addChild(monster,4);
		//设置锚点
		monster->setAnchorPoint(Vec2(0.5,0));
		monster->setPosition(init_x, init_y);
		//设置速度
		m_speed = SLOWSPEED;
		m_attack = BIGATTACK;
		//设置金币
		deadCost = BIGMONEY;
		//创建血条
		blood = ui::LoadingBar::create("monster/blood.png");
		if (!blood)
		{
			warning("blood.png");
		}
		else
		{
			//初始血量为100%
			blood->setPercent(100);
			//设置血条位置
			blood->setPosition(
				Vec2(monster->getPosition().x, 
					monster->getPosition().y + monster->getBoundingBox().size.height));
			//设置锚点
			blood->setAnchorPoint(Vec2(0.5, 0));

			this->addChild(blood,100);
			this->Animating();
		}
	}
	/*schedule([this](float dt)
		{
			this->Test(dt);
		}, 1.f, "Test");*/

	return true;
}




bool FastMonster::init(float init_x, float init_y)
{
	if (!Node::init())
	{
		return false;
	}

	//创建怪物精灵
	monster = Sprite::create("monster/fast1.png");
	if (!monster)
		warning("fast1.png");
	else
	{

		this->addChild(monster, 7);
		//设置锚点
		monster->setAnchorPoint(Vec2(0.5, 0));
		monster->setPosition(init_x, init_y);
		//设置速度
		m_speed = FASTSPEED;
		m_attack = NORMALATTACK;
		//设置金币
		deadCost = NORMALMONEY;

		//创建血条
		blood = ui::LoadingBar::create("monster/blood.png");
		if (!blood)
		{
			warning("blood.png");
		}
		else
		{
			//初始血量为100%
			blood->setPercent(100);
			//设置血条位置
			blood->setPosition(
				Vec2(monster->getPosition().x,
					monster->getPosition().y + monster->getBoundingBox().size.height));
			//设置锚点
			blood->setAnchorPoint(Vec2(0.5, 0));

			this->addChild(blood, 100);
			this->Animating();
		}
	}

	/*schedule([this](float dt)
		{
			this->Test(dt);
		}, 1.f, "Test");*/
	return true;
}

