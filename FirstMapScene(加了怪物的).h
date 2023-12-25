#ifndef __FIRSTMAPSCENE_H__
#define __FIRSTMAPSCENE_H__

#include"cocos2d.h"
#include"Monster.h"
#include "vector"

//该地图怪物入口位置
#define INITX1 200.f
#define INITY1 405.f


class FirstMapScene : public cocos2d::Scene {
public:
    int money = 200;
    int round = 0;
    static cocos2d::Scene* createScene();
    virtual bool init();

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

    void MonsterWave(const int type, const float blood,const int count,const float inr,
        Carrot* carrot,std::vector<Path> road);
    
    void checkWave(float dt);


};

#endif // __FIRSTMAPSCENE_H__
