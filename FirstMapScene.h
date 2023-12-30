#ifndef __FIRSTMAPSCENE_H__
#define __FIRSTMAPSCENE_H__

#include"vector"
#include"cocos2d.h"
#include"Monster.h"
#include"Carrot.h"
#include"MonsterManager.h"

//该地图怪物入口位置
#define INITX1 200.f
#define INITY1 405.f


struct WaveData
{
    int type;       //怪物种类
    int count;      //怪物波次
    int health;     //怪物生命值
    float interval;    //出现间隔
    std::string name;   //怪物波次标签
    WaveData(int type, int count, int health, float interval, const std::string& name)
    {
        this->type = type;
        this->count = count;
        this->health = health;
        this->interval = interval;
        this->name = name;
    }
};


class FirstMapScene : public cocos2d::Scene {
public:
    int money = 200;
    int round = 0;
    bool win = 0;
    Carrot* carrot;
    cocos2d::Label* RoundLabel;
    MonsterManager Monsters;        //怪物管理器
    std::vector<Path> road;         //怪物移动路径
    std::vector<WaveData> waves;    //怪物波次数据

    static cocos2d::Scene* createScene();
    virtual bool init();
    cocos2d::Label* createRoundLabel();
    void updateRoundLabel(float dt);
    void backToMain(cocos2d::Ref* sender);
    void changeSpeed(cocos2d::Ref* sender);
    void pause(cocos2d::Ref* sender);
    void removeAllMonster();
    void addMonsterToScene(Monster* monster)
    {
        Monsters.AddMonster(monster);
        monster->SetCarrot(carrot);
        addChild(monster, 5);

    }
    void firstTryAgain(cocos2d::Ref* sender);
    void updateFail(float dt);
    void updateWin(float dt);

    cocos2d::Label* label;
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {//监听用的
        cocos2d::Vec2 touchPos = touch->getLocation();
        updateMousePositionLabel(touchPos); //更新文本标签显示的鼠标/触摸坐标
        return true;
    }
    void updateMousePositionLabel(const cocos2d::Vec2& position) {//监听用的
        label->setString(cocos2d::StringUtils::format("Mouse Position: (%.0f, %.0f)", position.x, position.y));//更新文本标签的内容为当前鼠标/触摸坐标
    }

    CREATE_FUNC(FirstMapScene);


    /*=================有关怪物的函数=============*/

    /*
    * 可以生成一波怪物
    * type 种类  blood 血量  count 个数  inr 出现间隔 carrot 把萝卜当成参数传进去  road 怪物移动路径
    */
    void MonsterWave(const int type, const float blood, const int count, const float inr);

    void SpawnWave(const WaveData& wave);

    void StartWaves();

    void NextWaveCallback();

};

#endif // __FIRSTMAPSCENE_H__
