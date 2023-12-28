#pragma once
#ifndef _TOWER_H_
#define _TOWER_H_

#include"cocos2d.h"

USING_NS_CC;
/***************************************
* ��̨�Ļ��࣬������������̨�Ĺ�ͬ����
****************************************/
class Tower :public Sprite {
public:
	virtual bool init();

	static Tower* construct(Vec2 position, int choice);

	virtual void remove() { this->removeFromParentAndCleanup(true); }



	//	virtual void rotate();

	//	virtual void shoot();

	//	virtual bool isTargetInRange(); //����Ƿ��й�����Χ��Ŀ��

	//	virtual upgradeReminder(); //��ʾ����㹻������������������С��ͷͼ��
private:
	int level;//�ȼ�
	int constructCost;//����������
	int upgradeCost;//����������
	int attack;//����ǿ��
	int attack_range;//������Χ
	Sprite* myTower;
};


#endif