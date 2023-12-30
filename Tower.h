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
* 炮台的基类，包含了所有炮台的共同特性
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

	//	virtual bool isTargetInRange(); //检查是否有攻击范围内目标

	//  virtual void upgradeReminder(Scene* curr_scene); //提示金币足够，该炮塔可以升级的小箭头图标

	virtual void upgrade(Tower* tower); //升级

	virtual void attackAnimation();

	void shoot(Monster* targetMonster);

	void rotateToMonster(Monster* targetMonster);

private:
	Sprite* base;        //炮塔的底座，取决于炮塔种类

	Sprite* bullet;		//创建炮塔的子弹
	
	int tag;             //编号代表是哪个炮塔(0：bottle|1：shit|2：snow)
	int level;           //等级
	int construct_cost;  //建造所需金币，取决于炮塔种类
	int upgrade_cost;    //升级所需金币，取决于炮塔种类
	int attack_power;    //攻击强度,取决于炮塔等级
	int attack_range;    //攻击范围,取决于炮塔等级
	int bullet_speed;	 //子弹的发射速度
};


#endif
