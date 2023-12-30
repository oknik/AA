#ifndef __FIRSTMAPSCENE_H__
#define __FIRSTMAPSCENE_H__

#include"vector"
#include"cocos2d.h"
#include"Monster.h"
#include"Carrot.h"
#include"MonsterManager.h"

//�õ�ͼ�������λ��
#define INITX1 200.f
#define INITY1 405.f


struct WaveData
{
    int type;       //��������
    int count;      //���ﲨ��
    int health;     //��������ֵ
    float interval;    //���ּ��
    std::string name;   //���ﲨ�α�ǩ
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
    MonsterManager Monsters;        //���������
    std::vector<Path> road;         //�����ƶ�·��
    std::vector<WaveData> waves;    //���ﲨ������

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
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {//�����õ�
        cocos2d::Vec2 touchPos = touch->getLocation();
        updateMousePositionLabel(touchPos); //�����ı���ǩ��ʾ�����/��������
        return true;
    }
    void updateMousePositionLabel(const cocos2d::Vec2& position) {//�����õ�
        label->setString(cocos2d::StringUtils::format("Mouse Position: (%.0f, %.0f)", position.x, position.y));//�����ı���ǩ������Ϊ��ǰ���/��������
    }

    CREATE_FUNC(FirstMapScene);


    /*=================�йع���ĺ���=============*/

    /*
    * ��������һ������
    * type ����  blood Ѫ��  count ����  inr ���ּ�� carrot ���ܲ����ɲ�������ȥ  road �����ƶ�·��
    */
    void MonsterWave(const int type, const float blood, const int count, const float inr);

    void SpawnWave(const WaveData& wave);

    void StartWaves();

    void NextWaveCallback();

};

#endif // __FIRSTMAPSCENE_H__
