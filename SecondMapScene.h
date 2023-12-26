#ifndef __SECONDMAPSCENE_H__
#define __SECONDMAPSCENE_H__

#include "cocos2d.h"
#include "Monster.h"
#include <vector>

//第二张地图怪物的起始位置
#ifndef INITX2
#define INITX2 510.f
#endif

#ifndef INITY
#define INITY2 90.f
#endif

class SecondMapScene : public cocos2d::Scene {
public:
    int money = 200;
    int round = 0;
    static cocos2d::Scene* createScene();
    virtual bool init();

    cocos2d::Label* label;
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {//监听用的
        cocos2d::Vec2 touchPos = touch->getLocation();
        updateMousePositionLabel(touchPos); // 更新文本标签显示的鼠标/触摸坐标
        return true;
    }

    void updateMousePositionLabel(const cocos2d::Vec2& position) {//监听用的
        label->setString(cocos2d::StringUtils::format("Mouse Position: (%.0f, %.0f)", position.x, position.y));        // 更新文本标签的内容为当前鼠标/触摸坐标
    }
    CREATE_FUNC(SecondMapScene);

    void MonsterWave(const int type, const float blood, const int count, const float inr,
        Carrot* carrot, std::vector<Path> road);
};

#endif // __SECONDMAPSCENE_H__
