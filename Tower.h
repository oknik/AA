#pragma once
#ifndef _TOWER_H_
#define _TOWER_H_

#define BOTTLE 0
#define SHIT 1
#define SNOW 2

#include"cocos2d.h"
#include "Monster.h"

USING_NS_CC;
/***************************************
* ��̨�Ļ��࣬������������̨�Ĺ�ͬ����
****************************************/
class Tower :public Sprite {
public:
	virtual bool init(const std::string& filename);

	static Tower* construct(Vec2 position, int choice);

	virtual void remove() { this->removeFromParentAndCleanup(true); }

	Monster* getClosestMonster(const Vector<Monster*>& monsters);

	void updateTower(Vector<Monster*>monsters);

	//	virtual void rotate();

	//	virtual void shoot();

	//	virtual bool isTargetInRange(); //����Ƿ��й�����Χ��Ŀ��

	//  virtual void upgradeReminder(Scene* curr_scene); //��ʾ����㹻������������������С��ͷͼ��

	virtual void upgrade(Tower* tower); //����

	virtual void attackAnimation();

	void shoot(Monster* targetMonster);

	void rotateToMonster(Monster* targetMonster);

private:
	Sprite* base;        //�����ĵ�����ȡ������������

	Sprite* bullet;		//�����������ӵ�
	
	int tag;             //��Ŵ������ĸ�����(0��bottle|1��shit|2��snow)
	int level;           //�ȼ�
	int construct_cost;  //���������ң�ȡ������������
	int upgrade_cost;    //���������ң�ȡ������������
	int attack_power;    //����ǿ��,ȡ���������ȼ�
	int attack_range;    //������Χ,ȡ���������ȼ�
	int bullet_speed;	 //�ӵ��ķ����ٶ�
};


#endif
