#include "Monster.h"
#include "audio/include/AudioEngine.h"

void Monster::UpdateMonster(float dt)
{
	//ʵʱ���¹�������
	m_x = monster->getPosition().x;
	m_y = monster->getPosition().y;
	CCLOG("m_x=%f, m_y=%f", m_x, m_y);
	//�ж��Ƿ�����
	if (isDead())
	{
		DeadAnimate();
		scheduleOnce([this](float dt)
			{
				this->RemoveMonster();;
			}, 0.35f, "remove_monster");
	}
	// �ж��Ƿ������ܲ�
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
	c_blood -= damage;//��ǰѪ����ȥ�˺�
	if (c_blood < 0)
	{
		c_blood = 0;
	}
	blood->setPercent(float(c_blood) / m_blood * 100);//����Ѫ��
}

MoveBy* Monster::CreateAction(Path path)
{
	//���ɶ���
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
	//��ʱ����
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
	monster = Sprite::create(spriteName);	// �������ﾫ��
	if (!monster)
		CCLOG("Failed to load sprite: %s", spriteName.c_str());
	else
	{
		monster->setScale(scale);		//���ù����С
		monster->setPosition(init_x, init_y);	//����λ��
		monster->setAnchorPoint(Vec2(0.5, 0));// ����ê��

		m_speed = speed;	// �����ٶ�
		m_attack = attack;	//���ù�����
		m_deadcost = deadCost;	// ���ý��

		this->addChild(monster, 4);		//��ӵ����ڵ�
		
		blood = ui::LoadingBar::create("monster/blood.png");// ����Ѫ��

		if (!blood)
		{
			CCLOG("Failed to load sprite: monster/blood.png");
		}
		else
		{
			
			blood->setPercent(100);	// ��ʼѪ��Ϊ100%
			blood->setPosition(Vec2(init_x, init_y + monster->getBoundingBox().size.height));	//����λ��
			blood->setAnchorPoint(Vec2(0.5, 0));		//����ê��
			this->addChild(blood, 100);		//��ӵ����ڵ�

			this->Animating();		//���ɹ��ﶯ��

			//������ײ��
			//physicsbody = PhysicsBody::createBox(monster->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
			//PhysicsMaterial(0.1f, 1.0f, 0.0f) ��һ��������ʣ�������Ħ����������ϵ�����ܶȵȲ�����
			//����������Ħ����Ϊ 0.1f������ϵ��Ϊ 1.0f���ܶ�Ϊ 0.0f��
			//physicsbody->setDynamic(true);
			//����������Ϊ��̬���壬����ζ�������ܵ��������ö������˶���
			//physicsbody->setCategoryBitmask(0x01); 
			//���������������롣���������һ��32λ��������
			//���ڱ�ʶ����������������ֵͨ��ʹ��λ���������ã��Ա�����ײ���ʱ�ж�����֮��Ĺ�ϵ��
			//physicsbody->setCollisionBitmask(0x02);
			//�����������ײ���롣��ײ���붨���������������Щ�������巢����ײ��
			//physicsbody->setContactTestBitmask(0x03);
			//��������ĽӴ��������롣�Ӵ��������붨����������Լ����Щ�������塣
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
