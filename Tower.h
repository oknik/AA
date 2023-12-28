#pragma once
#ifndef _TOWER_H_
#define _TOWER_H_

#include"cocos2d.h"

USING_NS_CC;
/***************************************
* 炮台的基类，包含了所有炮台的共同特性
****************************************/
class Tower :public Sprite {
public:
	virtual bool init();

	static Tower* construct(Vec2 position, int choice);

	virtual void remove() { this->removeFromParentAndCleanup(true); }



	//	virtual void rotate();

	//	virtual void shoot();

	//	virtual bool isTargetInRange(); //检查是否有攻击范围内目标

	//	virtual upgradeReminder(); //提示金币足够，该炮塔可以升级的小箭头图标
private:
	int level;//等级
	int constructCost;//建造所需金币
	int upgradeCost;//升级所需金币
	int attack;//攻击强度
	int attack_range;//攻击范围
	Sprite* myTower;
};


#endif