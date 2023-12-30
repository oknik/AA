#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"audio/include/AudioEngine.h"
#include "Carrot.h"
#include <vector>

USING_NS_CC;

#ifndef __MONSTER_SCENE_H__
#define __MONSTER_SCENE_H__

//�����в�ͬ���ͣ���һ�º궨��
#define NORMALMONSTER 0
#define FASTMONSTER 1
#define BIGMONSTER 2
//�����в�ͬ�ٶ�
#define SLOWSPEED  40
#define NORMALSPEED 70
#define FASTSPEED 150
//����ҧ�ܲ������ͬ��Ѫ
#define NORMALATTACK 1
#define BIGATTACK 2
//����ᱬ���
#define NORMALMONEY 14
#define BIGMONEY 168
//����ĺ궨��
#define RIGHT 'r'
#define LEFT 'l'
#define UP 'u'
#define DOWN 'd'

//����·��
struct Path
{
	char dir;	//����
	float distance;		//����
	Path(char ch, float flt) :dir(ch), distance(flt) {};
};


//Monster���������
class Monster;

//NormalMonster�������
class NormalMonster;

//BigMonster�������
class BigMonster;

//FastMonster�������
class FastMonster;

//Monster����Ķ���
class Monster :public Node
{
private:
	//ͨ��Path���ɶ���ʵ��
	MoveBy* Monster::CreateAction(Path path);
protected:
	float m_blood;		//��ѪѪ��
	float c_blood;		//��ǰѪ��	
	int m_speed;		//�ٶ�
	int m_attack;		//ҧ�ܲ�������Ѫ
	float m_x, m_y;		//��������
	int m_deadcost;		//���˱����ٽ��
	bool isvalid = true;	//�ù����Ƿ���Ч
	Sprite* monster;	//����
	ui::LoadingBar* blood;	//Ѫ��
	Carrot* carrot;		//�ܲ�
	//PhysicsBody* physicsbody;		//��ײ��
public:
	//SpriteName��ͼƬ����	init_x�����x����	init_y�����y����	scale����С	speed���ٶ�	attack��������	deadCost�����
	bool init(const std::string& spriteName, float init_x, float init_y, float scale, int speed, int attack, int deadCost);
	//���¹���״̬
	void UpdateMonster(float dt);
	//��������
	void GetHurt(float damage);	
	//�жϹ����Ƿ�����
	bool isDead() { return c_blood <= 0; }
	//�жϹ����Ƿ���Ȼ��Ч
	bool isValid() { return isvalid; }
	//�����ܲ�
	void SetCarrot(Carrot* _carrot) { carrot = _carrot; }
	//ɾ������
	void RemoveMonster()
	{
		isvalid = false;
		unschedule("update_monster");
	}
	//�������
	void Emerge()
	{
		//���ֶ���û����Դ���Ǹ���Դ�Һ���̫����
		Vector<SpriteFrame*> emerge;
		emerge.pushBack(emerge);
		Animation* animation = Animation::createWithSpriteFrames(emerge, 0.1f);
		cocos2d::Animate* animate = Animate::create(animation);
		monster->runAction(animate);
		//���Ź��������Ч
		AudioEngine::play2d("monster/emerge.ogg", false);
	}
	//�����������麯��
	void DeadAnimate()
	{
		//��������
		Vector<SpriteFrame*> deadFrames;
		deadFrames.pushBack(SpriteFrame::create("monster/dead1.png", Rect(0, 0, 128, 128)));
		deadFrames.pushBack(SpriteFrame::create("monster/dead2.png", Rect(0, 0, 128, 128)));
		deadFrames.pushBack(SpriteFrame::create("monster/dead3.png", Rect(0, 0, 128, 128)));
		deadFrames.pushBack(SpriteFrame::create("monster/dead4.png", Rect(0, 0, 128, 128)));
		deadFrames.pushBack(SpriteFrame::create("monster/dead5.png", Rect(0, 0, 128, 128)));
		deadFrames.pushBack(SpriteFrame::create("monster/dead6.png", Rect(0, 0, 128, 128)));
		deadFrames.pushBack(SpriteFrame::create("monster/dead7.png", Rect(0, 0, 128, 128)));
		Animation* animation = Animation::createWithSpriteFrames(deadFrames, 0.3f);
		Animate* animate = Animate::create(animation);
		monster->runAction(RepeatForever::create(animate));
	}
	//����Ķ���
	virtual void Animating() = 0;
	//���������·�� vector<Path>&path,��ʱ float dt
	void Move(const std::vector<Path>& path, float dt = 0);
};

//��ͨ����
class NormalMonster :public Monster
{
public:
	//���캯��
	NormalMonster(float health) { m_blood = health; c_blood = health; }
	//��������
	static NormalMonster* create(float health, float init_x, float init_y) {
		NormalMonster* pRet = new(std::nothrow) NormalMonster(health);
		if (pRet && pRet->init(init_x, init_y)) {

			pRet->autorelease();
			return pRet;
		}
		else {
			delete pRet; pRet = nullptr; return nullptr;
		}
	};
	//��ʼ��
	bool init(float init_x, float init_y);
	//��������
	void Dead()
	{
		DeadAnimate();
		unschedule("update_monster");//ȡ��update_monster��schedule����
		AudioEngine::play2d("monster/mon2.ogg", false);//������Ч
	}
	//���ﱾ��Ķ���
	void Animating()
	{
		Vector<SpriteFrame*> animFrames;
		animFrames.pushBack(SpriteFrame::create("monster/normal1.png", Rect(0, 0, 68, 61)));
		animFrames.pushBack(SpriteFrame::create("monster/normal2.png", Rect(0, 0, 62, 61)));
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
		Animate* animate = Animate::create(animation);
		monster->runAction(RepeatForever::create(animate));
	}

};

//�����
class BigMonster :public Monster
{
public:
	//���캯��
	BigMonster(float health) { m_blood = health; c_blood = health; }
	//��������
	static BigMonster* create(float health, float init_x, float init_y) {
		BigMonster* pRet = new(std::nothrow) BigMonster(health);
		if (pRet && pRet->init(init_x, init_y)) {
			pRet->autorelease();
			return pRet;
		}
		else {
			delete pRet; pRet = nullptr; return nullptr;
		}
	};
	//��ʼ��
	bool init(float init_x, float init_y);
	//��������
	void Dead()
	{
		DeadAnimate();
		unschedule("update_monster");//ȡ��update_monster��schedule����
		AudioEngine::play2d("monster/mon6.ogg", false);//������Ч
	}
	//���ﱾ��Ķ���
	void Animating()
	{
		Vector<SpriteFrame*> animFrames;
		animFrames.pushBack(SpriteFrame::create("monster/big1.png", Rect(0, 0, 51, 54)));
		animFrames.pushBack(SpriteFrame::create("monster/big2.png", Rect(0, 0, 46, 54)));
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
		Animate* animate = Animate::create(animation);
		monster->runAction(RepeatForever::create(animate));
	}
};

//�ܵÿ�Ĺ���
class FastMonster :public Monster
{
public:
	//���캯��
	FastMonster(float health) { m_blood = health; c_blood = health; }
	//��������
	static FastMonster* create(float health, float init_x, float init_y) {
		FastMonster* pRet = new(std::nothrow) FastMonster(health);
		if (pRet && pRet->init(init_x, init_y)) {
			pRet->autorelease(); return pRet;
		}
		else {
			delete pRet; pRet = nullptr; return nullptr;
		}
	};
	//��ʼ��
	bool init(float init_x, float init_y);
	//��������
	void Dead()
	{
		DeadAnimate();
		unschedule("update_monster");//ȡ��update_monster��schedule����
		AudioEngine::play2d("monster/mon1.ogg", false);//������Ч
	}
	//���ﱾ��Ķ���
	void Animating()
	{
		Vector<SpriteFrame*> animFrames;
		animFrames.pushBack(SpriteFrame::create("monster/fast1.png", Rect(0, 0, 48, 51)));
		animFrames.pushBack(SpriteFrame::create("monster/fast2.png", Rect(0, 0, 50, 51)));
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
		Animate* animate = Animate::create(animation);
		monster->runAction(RepeatForever::create(animate));
	}
};

#endif
