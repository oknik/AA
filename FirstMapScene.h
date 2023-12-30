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

class FirstMapScene : public cocos2d::Scene {
public:
    int money = 200;
    int round = 1;
    bool win = 0;
    Carrot* carrot;
    cocos2d::Label* RoundLabel;

    MonsterManager Monsters;     //想拿这个来管理怪物

    std::vector<Path> road;  //该地图场景的路径

    

    static cocos2d::Scene* createScene();
    virtual bool init();
    cocos2d::Label* createRoundLabel();
    void updateRoundLabel(float dt);
    void backToMain(cocos2d::Ref* sender);
    void changeSpeed(cocos2d::Ref* sender);
    void pause(cocos2d::Ref* sender);
    void removeAllMonster();
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

    /*
   可以生成一波怪物
   type 种类  blood 血量  count 个数  inr 出现间隔 carrot 把萝卜当成参数传进去  road 怪物移动路径
   */

    void MonsterWave(const int type, const float blood, const int count, const float inr);


    //貌似怪物一波波定义只能写在这里了。。。我想不出更好的方法。。。

    void FirstMapScene::Wave1();
    void FirstMapScene::Wave2();
    void FirstMapScene::Wave3();
    void FirstMapScene::Wave4();
    void FirstMapScene::Wave5();
    void FirstMapScene::Wave6();
    void FirstMapScene::Wave7();
    void FirstMapScene::Wave8();
    void FirstMapScene::Wave9();
    void FirstMapScene::Wave10();


};

#endif // __FIRSTMAPSCENE_H__
