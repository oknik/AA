#ifndef __FIRSTMAPSCENE_H__
#define __FIRSTMAPSCENE_H__

#include"vector"
#include"cocos2d.h"
#include"Monster.h"
#include"Carrot.h"

//�õ�ͼ�������λ��
#define INITX1 200.f
#define INITY1 405.f

class FirstMapScene : public cocos2d::Scene {
public:
    int money = 200;
    int round = 0;
    Carrot* carrot;
    Vector <Monster*> monsters;     //����������������
    std::vector<Path> road;  //�õ�ͼ������·��


    static cocos2d::Scene* createScene();
    virtual bool init();
    void backToMain(cocos2d::Ref* sender);
    void removeAllMonster();
    void firstTryAgain(cocos2d::Ref* sender);
    void updateFail(float dt);
    


    cocos2d::Label* label;
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {//�����õ�
        cocos2d::Vec2 touchPos = touch->getLocation();
        updateMousePositionLabel(touchPos); //�����ı���ǩ��ʾ�����/��������
        return true;
    }

    void updateMousePositionLabel(const cocos2d::Vec2& position) {//�����õ�
        label->setString(cocos2d::StringUtils::format("Mouse Position: (%.0f, %.0f)", position.x, position.y));//�����ı���ǩ������Ϊ��ǰ���/��������
    }

    CREATE_FUNC(FirstMapScene);

    /*
   ��������һ������
   type ����  blood Ѫ��  count ����  inr ���ּ�� carrot ���ܲ����ɲ�������ȥ  road �����ƶ�·��
   */
    void MonsterWave(const int type, const float blood, const int count, const float inr);

    bool checkWave(float dt);


    //ò�ƹ���һ��������ֻ��д�������ˡ��������벻�����õķ���������

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
