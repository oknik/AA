#include "Monster.h"
#include "audio/include/AudioEngine.h"


static void warning(const char* filename)
{
	CCLOG("Error while loading: %s\n", filename);
}

void Monster::UpdateMonster(float dt)
{
	//ʵʱ���¹�������
	m_x = monster->getPosition().x;
	m_y = monster->getPosition().y;
	CCLOG("m_x=%d, m_y=%d", m_x, m_y);
	//�ж��Ƿ�����
	if (isDead())
	{
		Dead();
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
		RemoveMonster();
	}
}

void Monster::GetHurt(float damage)
{
	//��ǰѪ����ȥ�˺�
	c_blood -= damage;
	if (c_blood < 0)
	{
		c_blood = 0;
	}
	//����Ѫ��
	blood->setPercent(float(c_blood) / m_blood * 100);
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


bool NormalMonster::init(float init_x, float init_y)
{
	if (!Node::init())
	{
		return false;
	}

	//�������ﾫ��
	monster = Sprite::create("monster/normal1.png");
	if (!monster)
		warning("normal1.png");
	else
	{
		this->addChild(monster,4);
		//����ê��
		monster->setAnchorPoint(Vec2(0.5,0));
		monster->setPosition(init_x, init_y);
		//�����ٶ�
		m_speed = NORMALSPEED;
		m_attack = NORMALATTACK;

		//����Ѫ��
		blood = ui::LoadingBar::create("monster/blood.png");
		if (!blood)
		{
			warning("blood.png");
		}
		else
		{
			//��ʼѪ��Ϊ100%
			blood->setPercent(100);
			//����Ѫ��λ��
			blood->setPosition(
				Vec2(monster->getPosition().x, 
					monster->getPosition().y + monster->getBoundingBox().size.height));
			//����ê��
			blood->setAnchorPoint(Vec2(0.5, 0));

			this->addChild(blood,100);
			this->Animating();
		}
	}

	//�ص����������¹����״̬
	schedule([this](float dt)
		{
			this->UpdateMonster(dt);
		}, 0.1f, "update_monster");
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

	//�������ﾫ��
	monster = Sprite::create("monster/big1.png");
	if (!monster)
		warning("big1.png");
	else
	{
		monster->setScale(1.7f);

		this->addChild(monster,4);
		//����ê��
		monster->setAnchorPoint(Vec2(0.5,0));
		monster->setPosition(init_x, init_y);
		//�����ٶ�
		m_speed = SLOWSPEED;
		m_attack = BIGATTACK;

		//����Ѫ��
		blood = ui::LoadingBar::create("monster/blood.png");
		if (!blood)
		{
			warning("blood.png");
		}
		else
		{
			//��ʼѪ��Ϊ100%
			blood->setPercent(100);
			//����Ѫ��λ��
			blood->setPosition(
				Vec2(monster->getPosition().x, 
					monster->getPosition().y + monster->getBoundingBox().size.height));
			//����ê��
			blood->setAnchorPoint(Vec2(0.5, 0));

			this->addChild(blood,100);
			this->Animating();
		}
	}

	//�ص����������¹����״̬
	schedule([this](float dt)
		{
			this->UpdateMonster(dt);
		}, 0.1f, "update_monster");
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

	//�������ﾫ��
	monster = Sprite::create("monster/fast1.png");
	if (!monster)
		warning("fast1.png");
	else
	{

		this->addChild(monster, 7);
		//����ê��
		monster->setAnchorPoint(Vec2(0.5, 0));
		monster->setPosition(init_x, init_y);
		//�����ٶ�
		m_speed = FASTSPEED;
		m_attack = NORMALATTACK;

		//����Ѫ��
		blood = ui::LoadingBar::create("monster/blood.png");
		if (!blood)
		{
			warning("blood.png");
		}
		else
		{
			//��ʼѪ��Ϊ100%
			blood->setPercent(100);
			//����Ѫ��λ��
			blood->setPosition(
				Vec2(monster->getPosition().x,
					monster->getPosition().y + monster->getBoundingBox().size.height));
			//����ê��
			blood->setAnchorPoint(Vec2(0.5, 0));

			this->addChild(blood, 100);
			this->Animating();
		}
	}

	//�ص����������¹����״̬
	schedule([this](float dt)
		{
			this->UpdateMonster(dt);
		}, 0.1f, "update_monster");
	/*schedule([this](float dt)
		{
			this->Test(dt);
		}, 1.f, "Test");*/
	return true;
}


