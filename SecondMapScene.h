#ifndef __SECONDMAPSCENE_H__
#define __SECONDMAPSCENE_H__

#include "cocos2d.h"
#include "Monster.h"
#include <vector>

//�ڶ��ŵ�ͼ�������ʼλ��
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
    Carrot* carrot;
    static cocos2d::Scene* createScene();
    virtual bool init();
    void backToMain(cocos2d::Ref* sender);
    void removeAllMonster();
    void secondTryAgain(cocos2d::Ref* sender);
    void updateFail(float dt);


    cocos2d::Label* label;
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {//�����õ�
        cocos2d::Vec2 touchPos = touch->getLocation();
        updateMousePositionLabel(touchPos); // �����ı���ǩ��ʾ�����/��������
        return true;
    }

    void updateMousePositionLabel(const cocos2d::Vec2& position) {//�����õ�
        label->setString(cocos2d::StringUtils::format("Mouse Position: (%.0f, %.0f)", position.x, position.y));        // �����ı���ǩ������Ϊ��ǰ���/��������
    }
    CREATE_FUNC(SecondMapScene);

    void MonsterWave(const int type, const float blood, const int count, const float inr,
        Carrot* carrot, std::vector<Path> road);
};

#endif // __SECONDMAPSCENE_H__
