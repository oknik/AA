#include"audio/include/AudioEngine.h"
#include"Data.h"
#include"HelloWorldScene.h"
#include"MapSelectionScene.h"
#include"FirstMapScene.h"
#include"Object.h"
#include"Tower.h"

#include<vector>


USING_NS_CC;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* FirstMapScene::createScene() {
    auto scene = FirstMapScene::create();
    return scene;
}

cocos2d::Label* FirstMapScene::createRoundLabel() {
    RoundLabel = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("%d      10 rounds", round), "fonts/Marker Felt.ttf", 24);
    if (!RoundLabel) {
        CCLOG("Error creating HP Label");
    }
    return RoundLabel;
}

void FirstMapScene::updateRoundLabel(float dt) {
    if (RoundLabel) {
        RoundLabel->setString(cocos2d::StringUtils::format("%d      10 rounds", round));
    }

}


void FirstMapScene::backToMain(cocos2d::Ref* sender) {
    isFirstMapWon = true;
    int selectId = cocos2d::AudioEngine::play2d("test/Select.mp3", false);//�����true or false��ѭ������˼
    this->schedule([=](float dt) {
        if (cocos2d::AudioEngine::getState(selectId) != cocos2d::AudioEngine::AudioState::PLAYING) {
            cocos2d::AudioEngine::stopAll();
            this->unschedule("checkAudioFinished");
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.0f, HelloWorld::createScene()));// ����Ƶ������Ϻ�ִ���л������Ĳ���
        }
        }, "checkAudioFinished");
}

void FirstMapScene::pause(cocos2d::Ref* sender) {
    if (Director::getInstance()->isPaused()) {
        Director::getInstance()->resume(); // �ָ�����������
    }
    else {
        Director::getInstance()->pause(); // ��ͣ����������
    }
}


void FirstMapScene::removeAllMonster() {
    auto children = this->getChildren();
    for (auto child : children) {
        auto monster = dynamic_cast<Monster*>(child);
        if (monster) {
            this->removeChild(monster);
        }
    }
}

void FirstMapScene::firstTryAgain(cocos2d::Ref* sender) {
    cocos2d::AudioEngine::play2d("test/Select.mp3", false);
    carrot->hp = 10;
    money = 200;
    round = 1;
    win = 0;

    this->removeChildByName("FailSprite");
    this->removeChildByName("TryAgainMenu");
    this->removeChildByName("SelectMenu");
    this->removeAllMonster();

    std::vector<Path> road;
    road.push_back(Path(RIGHT, 118.f));
    road.push_back(Path(DOWN, 260.f));
    road.push_back(Path(RIGHT, 370.f));
    road.push_back(Path(UP, 260.f));
    road.push_back(Path(RIGHT, 118.f));

    scheduleOnce([this, myCarrot = carrot](float dt)
        {
            Wave1();
        }, 0.f, "MonsterWave");

    
}

void FirstMapScene::updateFail(float dt) {
    auto failSprite = this->getChildByName("FailSprite");
    auto tryAgainMenu = this->getChildByName("TryAgainMenu");
    auto selectMenu = this->getChildByName("SelectMenu");

    if (carrot->hp == 0 && !failSprite && !tryAgainMenu) {
        cocos2d::AudioEngine::play2d("test/Lose.ogg", false);
        failSprite = Sprite::create("test/Fail.png");
        failSprite->setPosition(Vec2(500, 300));
        failSprite->setName("FailSprite");
        this->addChild(failSprite, 11);
        Director::getInstance()->getActionManager()->pauseAllRunningActions();
        unschedule("update_monsters");

        auto failRoundLabel = Label::createWithTTF(StringUtils::format("%d    10", round), "fonts/Marker Felt.ttf", 18);
        if (failRoundLabel) {
            failRoundLabel->setPosition(Vec2(526, 317));
            this->addChild(failRoundLabel, 11);
        }

        auto failMapLabel = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 18);
        if (failMapLabel) {
            failMapLabel->setPosition(Vec2(443, 282));
            this->addChild(failMapLabel, 11);
        }


        auto selectItem = MenuItemImage::create(
            "test/SelectNormal.png",
            "test/SelectSelected.png",
            [](Ref* sender) {
                Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MapSelectionScene::createScene()));
            }
        );
        if (selectItem) {
            selectItem->setPosition(415, 248);
            auto menu = cocos2d::Menu::create(selectItem, nullptr);
            menu->setPosition(cocos2d::Vec2::ZERO);
            this->addChild(menu, 12);
            menu->setName("SelectMenu");
        }
        else {
            CCLOG("Failed to load select button");
        }


        auto tryAgainItem = MenuItemImage::create(
            "test/TryAgainNormal.png",
            "test/TryAgainSelected.png",
            CC_CALLBACK_1(FirstMapScene::firstTryAgain, this));

        if (tryAgainItem) {
            tryAgainItem->setPosition(Vec2(558, 248));
            auto menu = Menu::create(tryAgainItem, nullptr);
            menu->setPosition(Vec2::ZERO);
            this->addChild(menu, 12);
            menu->setName("TryAgainMenu");
        }
        else {
            CCLOG("Failed to load try again button");
        }
    }
}
void FirstMapScene::updateWin(float dt) {
    auto winSprite = this->getChildByName("WinSprite");
    auto tryAgainMenu = this->getChildByName("TryAgainMenu");
    auto selectMenu = this->getChildByName("SelectMenu");

    if (win == 1 && !winSprite && !tryAgainMenu) {
        cocos2d::AudioEngine::play2d("test/Victory.ogg", false);
        winSprite = Sprite::create("test/Win.png");
        winSprite->setPosition(Vec2(500, 300));
        winSprite->setName("WinSprite");
        this->addChild(winSprite, 11);
        Director::getInstance()->getActionManager()->pauseAllRunningActions();
        unschedule("update_monsters");

        auto selectItem = MenuItemImage::create(
            "test/SelectNormal.png",
            "test/SelectSelected.png",
            [](Ref* sender) {
                Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MapSelectionScene::createScene()));
            }
        );
        if (selectItem) {
            selectItem->setPosition(415, 248);
            auto menu = cocos2d::Menu::create(selectItem, nullptr);
            menu->setPosition(cocos2d::Vec2::ZERO);
            this->addChild(menu, 12);
            menu->setName("SelectMenu");
        }
        else {
            CCLOG("Failed to load select button");
        }


        auto tryAgainItem = MenuItemImage::create(
            "test/TryAgainNormal.png",
            "test/TryAgainSelected.png",
            CC_CALLBACK_1(FirstMapScene::firstTryAgain, this));

        if (tryAgainItem) {
            tryAgainItem->setPosition(Vec2(558, 248));
            auto menu = Menu::create(tryAgainItem, nullptr);
            menu->setPosition(Vec2::ZERO);
            this->addChild(menu, 12);
            menu->setName("TryAgainMenu");
        }
        else {
            CCLOG("Failed to load try again button");
        }
    }
}


void FirstMapScene::changeSpeed(Ref* sender) {
    float currentTimeScale = Director::getInstance()->getScheduler()->getTimeScale();
    if (currentTimeScale == 1.0f) {
        Director::getInstance()->getScheduler()->setTimeScale(1.5f);
    }
    else {
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);
    }
}

bool FirstMapScene::init() {
    if (!Scene::init()) {
        return false;
    }


    //����һ��������
    /*label = cocos2d::Label::createWithTTF("Mouse Position: (0, 0)", "fonts/arial.ttf", 24);
    label->setPosition(cocos2d::Vec2(300, 300)); // ����λ��
    this->addChild(label, 1);
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(FirstMapScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);*/

    cocos2d::AudioEngine::stopAll();
    cocos2d::AudioEngine::play2d("test/PlayBGM.mp3", true);

    auto sprite = cocos2d::Sprite::create("test/SelectBG.png");
    if (sprite == nullptr)
    {
        problemLoading("'test/SelectBG.png'");
    }
    else
    {
        sprite->setScale(1000.0f / sprite->getContentSize().width, 600.0f / sprite->getContentSize().height);//����ͼƬ��С��Ҫ�����п��Ӧ
        sprite->setPosition(cocos2d::Vec2(500, 300));
        this->addChild(sprite, 0);
    }

    auto path = cocos2d::Sprite::create("test/Path1.png");
    if (path == nullptr)
    {
        problemLoading("'test/Path1.png'");
    }
    else
    {
        path->setScale(1000.0f / path->getContentSize().width, 600.0f / path->getContentSize().height);//����ͼƬ��С��Ҫ�����п��Ӧ
        path->setPosition(cocos2d::Vec2(500, 300));
        this->addChild(path, 0);
    }

    auto upBoard = cocos2d::Sprite::create("test/UpBoard.png");
    if (upBoard == nullptr)
    {
        problemLoading("'test/UpBoard.png'");
    }
    else
    {
        upBoard->setPosition(cocos2d::Vec2(500, 571));
        this->addChild(upBoard, 0);
    }

    auto upBoard2 = cocos2d::Sprite::create("test/UpBoard2.png");
    if (upBoard == nullptr)
    {
        problemLoading("'test/UpBoard2.png'");
    }
    else
    {
        upBoard2->setPosition(cocos2d::Vec2(537, 571));
        this->addChild(upBoard2, 0);
    }

    auto moneyLabel = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("%d", money), "fonts/Marker Felt.ttf", 24);
    if (moneyLabel) {
        moneyLabel->setPosition(cocos2d::Vec2(200, 575));
        this->addChild(moneyLabel);
    }
    else {
        CCLOG("Error creating Label");
    }

    auto roundLabel = createRoundLabel();
    if (roundLabel) {
        roundLabel->setPosition(cocos2d::Vec2(540, 575));
        this->addChild(roundLabel);
    }
    else {
        CCLOG("Error creating Round Label");
    }
    auto speedUpItem1 = MenuItemImage::create("test/Speed_1.png", "test/Speed_1.png");
    auto speedUpItem2 = MenuItemImage::create("test/Speed_2.png", "test/Speed_2.png");
    auto speedUp = MenuItemToggle::createWithCallback(CC_CALLBACK_1(FirstMapScene::changeSpeed, this), speedUpItem1, speedUpItem2, nullptr);

    if (speedUp) {
        speedUp->setPosition(Vec2(730,570));
        auto menu = Menu::create(speedUp, nullptr);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu);
    }

    auto pauseItem1 = MenuItemImage::create("test/Pause.png", "test/Pause.png");
    auto pauseItem2 = MenuItemImage::create("test/Restart.png", "test/Restart.png");
    auto pauseItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(FirstMapScene::pause, this), pauseItem1, pauseItem2, nullptr);

    if (pauseItem) {
        pauseItem->setPosition(Vec2(800, 570)); 
        auto menu = Menu::create(pauseItem, nullptr);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu); 
    }

    auto BackItem = cocos2d::MenuItemImage::create(
        "test/BackNormal.png",
        "test/BackSelected.png",
        CC_CALLBACK_1(FirstMapScene::backToMain, this));
    if (BackItem) {
        BackItem->setPosition(cocos2d::Vec2(850, 575));
        auto menu = cocos2d::Menu::create(BackItem, nullptr); // �����˵�����ӷ��ذ�ť
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu);
    }
    else {
        CCLOG("Failed to load back button"); // �������ʧ�ܣ����������Ϣ
    }

    auto tree1 = Tree::createTree();
    tree1->setPosition(cocos2d::Vec2(194, 374));
    this->addChild(tree1);

    auto tree2 = Tree::createTree();
    tree2->setPosition(cocos2d::Vec2(265, 225));
    this->addChild(tree2);

    auto tree3 = Tree::createTree();
    tree3->setPosition(cocos2d::Vec2(736, 225));
    this->addChild(tree3);

    auto tree4 = Tree::createTree();
    tree4->setPosition(cocos2d::Vec2(809, 374));
    this->addChild(tree4);

    auto ice1 = Ice::createIce();
    ice1->setPosition(cocos2d::Vec2(245, 475));
    this->addChild(ice1);

    auto ice2 = Ice::createIce();
    ice2->setPosition(cocos2d::Vec2(365, 475));
    this->addChild(ice2);

    auto ice3 = Ice::createIce();
    ice3->setPosition(cocos2d::Vec2(365, 380));
    this->addChild(ice3);

    auto ice4 = Ice::createIce();
    ice4->setPosition(cocos2d::Vec2(415, 380));
    this->addChild(ice4);

    auto ice5 = Ice::createIce();
    ice5->setPosition(cocos2d::Vec2(512, 280));
    this->addChild(ice5);

    auto ice6 = Ice::createIce();
    ice6->setPosition(cocos2d::Vec2(589, 380));
    this->addChild(ice6);

    auto ice7 = Ice::createIce();
    ice7->setPosition(cocos2d::Vec2(589, 100));
    this->addChild(ice7);

    auto bigIce1 = BigIce::createBigIce();
    bigIce1->setPosition(cocos2d::Vec2(365, 100));
    this->addChild(bigIce1);

    auto bigIce2 = BigIce::createBigIce();
    bigIce2->setPosition(cocos2d::Vec2(591, 225));
    this->addChild(bigIce2);

    auto icecream = Icecream::createIcecream();
    icecream->setPosition(cocos2d::Vec2(365, 225));
    this->addChild(icecream);

    auto house = House::createHouse();
    house->setPosition(cocos2d::Vec2(591, 435));
    this->addChild(house);

    auto hpSprite = Carrot::createHP();
    hpSprite->setPosition(cocos2d::Vec2(810, 520));
    this->addChild(hpSprite);

    carrot = Carrot::createCarrot();
    carrot->setPosition(cocos2d::Vec2(810, 485));
    this->addChild(carrot);

    auto HPLabel = carrot->HPLabel;
    if (HPLabel) {
        HPLabel->setPosition(Vec2(800, 520));
        HPLabel->setTextColor(Color4B::BLACK);
        this->addChild(HPLabel);
    }

    carrot->schedule([this](float dt) {
        this->carrot->updateCarrotSprite();
        this->carrot->updateHPLabel();
        }, 0.1f, "update_carrot_hp");


    this->schedule(CC_SCHEDULE_SELECTOR(FirstMapScene::updateRoundLabel), 0.1f);
    this->schedule(CC_SCHEDULE_SELECTOR(FirstMapScene::updateWin), 0.1f);
    this->schedule(CC_SCHEDULE_SELECTOR(FirstMapScene::updateFail), 0.1f);


    auto hpButton = cocos2d::MenuItemImage::create("test/Update.png", "test/Update.png", [=](cocos2d::Ref* sender) {
        if (money >= 500) {
            carrot->hp += 1;
            money -= 500;
            carrot->updateCarrotSprite();//�޸��ܲ�ͼ��
            moneyLabel->setString(cocos2d::StringUtils::format("%d", money));//�޸�moneyLable
            cocos2d::AudioEngine::play2d("test/Select.mp3", false);
        }
        else {
            cocos2d::AudioEngine::play2d("test/Wrong.mp3", false);
        }
        });
    if (hpButton) {
        hpButton->setPosition(cocos2d::Vec2(850, 470));
        auto menu = cocos2d::Menu::create(hpButton, nullptr);
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu);
        auto Label = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("500"), "fonts/Marker Felt.ttf", 10);
        if (Label) {
            Label->setPosition(cocos2d::Vec2(852, 455));
            Label->setTextColor(cocos2d::Color4B::BLACK);
            this->addChild(Label);
        }
        else {
            CCLOG("Error creating Label");
        }
    }
    else {
        CCLOG("Error creating HP Button");
    }

    schedule(CC_SCHEDULE_SELECTOR(FirstMapScene::update), 1.0f);

    //��ͼ��·������
    road.push_back(Path(RIGHT, 118.f));
    road.push_back(Path(DOWN, 260.f));
    road.push_back(Path(RIGHT, 370.f));
    road.push_back(Path(UP, 260.f));
    road.push_back(Path(RIGHT, 118.f));



/*====================������̨ѡ�����=========================*/
    //������Ч�Ĳ�����Χ����������
    Rect validArea = Rect(100, 100, 800, 400);  //��Ч��Χ���ڷ�Χ�ڿ��Է�������

    //����ѡ����̨ʱ�Ķ�λ�׿�
    auto blank = Sprite::create("tower/blank.png");
    if (blank == nullptr) {
        problemLoading("'blank.png'");
    }
    else {
        this->addChild(blank, 0);
        blank->setVisible(false);
    }
    blank->setScale(0.6); //���µ����׿��С

    //������̨ѡ�����
    auto pickBottle = Sprite::create("tower/pickBottle.png");
    if (pickBottle == nullptr) {
        problemLoading("'pickbottle.png'");
    }
    else {
        this->addChild(pickBottle, 0);
        pickBottle->setVisible(false);
    }

    auto pickShit = Sprite::create("tower/pickShit.png");
    if (pickShit == nullptr) {
        problemLoading("'pickshit.png'");
    }
    else {
        this->addChild(pickShit, 0);
        pickShit->setVisible(false);
    }
    pickShit->setScale(0.6); //���µ�����С

    auto pickSnow = Sprite::create("tower/pickSnow.png");
    if (pickSnow == nullptr) {
        problemLoading("'picksnow.png'");
    }
    else {
        this->addChild(pickSnow, 0);
        pickSnow->setVisible(false);
    }
    pickSnow->setScale(0.6); //���µ�����С

    /**********************************��ʾ��������֪����������ģ���Ҫ�Ľ�Tower��
    Tower* bottle = Tower::create(Vec2(500, 300), BOTTLE);
    if (bottle)
        this->addChild(bottle);
    ***********************************/

    //������,�������λ�ã��ڵ��ʱ��ʾѡ����̨�Ķ�λ�׿�
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [blank, pickBottle, pickShit, pickSnow, validArea, this](Touch* touch, Event* event) {
        Vec2 touchPos = touch->getLocation();
        if (!blank->isVisible()) { //��ѡ��򲻿ɼ�ʱ
            if (validArea.containsPoint(touchPos)) { //���ڷ�Χ�ڣ���ʾ��̨ѡ��
                blank->setPosition(Vec2(touchPos.x, touchPos.y));
                blank->setVisible(true);
                pickBottle->setPosition(Vec2(touchPos.x, touchPos.y + 45));
                pickBottle->setVisible(true);
                pickShit->setPosition(Vec2(touchPos.x - 45, touchPos.y + 45));
                pickShit->setVisible(true);
                pickSnow->setPosition(Vec2(touchPos.x + 45, touchPos.y + 45));
                pickSnow->setVisible(true);
            }
            else {  //�����ڷ�Χ�ڣ����Ŵ�����Ч������ʾѡ��
                blank->setVisible(false);
                pickBottle->setVisible(false);
                pickShit->setVisible(false);
                pickSnow->setVisible(false);
                AudioEngine::play2d("test/Wrong.mp3", false);
                return false;
            }
        }
        else {//��ѡ���ɼ�ʱ
            Vec2 choice = touch->getLocation();
            if (pickBottle->getBoundingBox().containsPoint(choice)) {  //ѡ��ƿ����
                Vec2 blankPos = blank->getPosition();
                auto bottle = Sprite::create("tower/bottle1.png");
                if (bottle == nullptr) {
                    problemLoading("'bottle1.png'");
                }
                else {
                    bottle->setPosition(blankPos);
                    blank->setVisible(false);
                    pickBottle->setVisible(false);
                    pickShit->setVisible(false);
                    pickSnow->setVisible(false);
                    this->addChild(bottle, 0);
                }
            }
            if (pickShit->getBoundingBox().containsPoint(choice)) {  //ѡ�б��
                Vec2 blankPos = blank->getPosition();
                auto shit = Sprite::create("tower/shit1.png");
                if (shit == nullptr) {
                    problemLoading("'shit1.png'");
                }
                else {
                    shit->setPosition(blankPos);
                    blank->setVisible(false);
                    pickBottle->setVisible(false);
                    pickShit->setVisible(false);
                    pickSnow->setVisible(false);
                    this->addChild(shit, 0);
                }
            }
            if (pickSnow->getBoundingBox().containsPoint(choice)) {  //ѡ��ѩ��
                Vec2 blankPos = blank->getPosition();
                auto snow = Sprite::create("tower/snow1.png");
                if (snow == nullptr) {
                    problemLoading("'snow1.png'");
                }
                else {
                    snow->setPosition(blankPos);
                    blank->setVisible(false);
                    pickBottle->setVisible(false);
                    pickShit->setVisible(false);
                    pickSnow->setVisible(false);
                    this->addChild(snow, 0);
                }
            }
        }
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    

/*=======================����=======================*/

  

   scheduleOnce([this, myCarrot = carrot](float dt)
        {
            Wave1();
        }, 0.f, "MonsterWave");

    //�¼�������
    /*auto customListener = EventListenerCustom::create("WaveCompleted", CC_CALLBACK_1(FirstMapScene::SecondWaveTriggered, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(customListener, this);*/

    return true;
}

void FirstMapScene::MonsterWave(const int type, const float blood, const int count, const float inr)
{
    
    std::map<int, std::function<Monster* ()>> monsterCreators;
    monsterCreators[NORMALMONSTER] = [&]() { return NormalMonster::create(blood, INITX1, INITY1); };
    monsterCreators[FASTMONSTER] = [&]() { return FastMonster::create(blood, INITX1, INITY1); };
    monsterCreators[BIGMONSTER] = [&]() { return BigMonster::create(blood, INITX1, INITY1); };

    for (int i = 0; i < count; i++)
    {
        if (monsterCreators.find(type) != monsterCreators.end())
        {
            Monster* monster = monsterCreators[type]();
            monster->SetCarrot(carrot);
            Monsters.AddMonster(monster);
            this->addChild(monster, 5);
            monster->Move(road, float(inr * i));
            //��ײ���ʵ��
            //auto contactListener = EventListenerPhysicsContact::create();   //������ײ����������
            //contactListener->onContactBegin = CC_CALLBACK_1(Monster::onContactBegin, monster);  //Ϊ���������ûص�����
            //_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
            //����ײ������ע�ᵽ�������¼��������У�ʹ���ܹ����ղ�����������ײ�¼���
        }
    }
    schedule([](float dt) {
        MonsterManager::UpdateMonsters(dt);
        }, 0.1f, "update_monsters");
}



void FirstMapScene::Wave1()
{
    scheduleOnce([this](float dt)
        {
            MonsterWave(FASTMONSTER, 70, 10, 1.f); // ����ִ����������������߼�
            schedule([this](float dt)
                {
                    if (Monsters.CheckWave())
                    {
                        round++;
                        Wave2();
                        unschedule("checkWave");
                    }
                    CCLOG("hahahah");
                }, 0.1f, "checkWave");
        }, 5.f, "firstWave");
}


void FirstMapScene::Wave2()
{
    scheduleOnce([this](float dt)
        {
            MonsterWave(NORMALMONSTER, 100, 10, 1.f); // ����ִ����������������߼�
            schedule([this](float dt)
                {
                    if (Monsters.CheckWave())
                    {
                        round++;
                        Wave3();
                        unschedule("checkWave");
                    }
                    CCLOG("hahahah");
                }, 0.1f, "checkWave");
        }, 5.f, "secondWave");
}
void FirstMapScene::Wave3()
{
    scheduleOnce([this](float dt)
        {
            MonsterWave(NORMALMONSTER, 100, 20, 1.f); // ����ִ����������������߼�
            schedule([this](float dt)
                {
                    if (Monsters.CheckWave())
                    {
                        round++;
                        Wave4();
                        unschedule("checkWave");
                    }
                    CCLOG("hahahah");
                }, 0.1f, "checkWave");
        }, 5.f, "firstWave");
}
void FirstMapScene::Wave4()
{
    scheduleOnce([this](float dt)
        {
            MonsterWave(BIGMONSTER, 70, 2, 3.f); // ����ִ����������������߼�
            schedule([this](float dt)
                {
                    if (Monsters.CheckWave())
                    {
                        round++;
                        Wave5();
                        unschedule("checkWave");
                    }
                    CCLOG("hahahah");
                }, 0.1f, "checkWave");
        }, 5.f, "firstWave");
}
void FirstMapScene::Wave5()
{
    scheduleOnce([this](float dt)
        {
            MonsterWave(NORMALMONSTER, 100, 20, 1.f); // ����ִ����������������߼�
            schedule([this](float dt)
                {
                    if (Monsters.CheckWave())
                    {
                        round++;
                        Wave6();
                        unschedule("checkWave");
                    }
                    CCLOG("hahahah");
                }, 0.1f, "checkWave");
        }, 5.f, "firstWave");
}
void FirstMapScene::Wave6()
{
    scheduleOnce([this](float dt)
        {
            MonsterWave(NORMALMONSTER, 100, 20, 1.f); // ����ִ����������������߼�
            schedule([this](float dt)
                {
                    if (Monsters.CheckWave())
                    {
                        round++;
                        Wave7();
                        unschedule("checkWave");
                    }
                    CCLOG("hahahah");
                }, 0.1f, "checkWave");
        }, 5.f, "firstWave");
}
void FirstMapScene::Wave7()
{
    scheduleOnce([this](float dt)
        {
            MonsterWave(NORMALMONSTER, 100, 20, 1.f); // ����ִ����������������߼�
            schedule([this](float dt)
                {
                    if (Monsters.CheckWave())
                    {
                        round++;
                        Wave8();
                        unschedule("checkWave");
                    }
                    CCLOG("hahahah");
                }, 0.1f, "checkWave");
        }, 5.f, "firstWave");
}
void FirstMapScene::Wave8()
{
    scheduleOnce([this](float dt)
        {
            MonsterWave(NORMALMONSTER, 100, 20, 1.f); // ����ִ����������������߼�
            schedule([this](float dt)
                {
                    if (Monsters.CheckWave())
                    {
                        round++;
                        Wave9();
                        unschedule("checkWave");
                    }
                    CCLOG("hahahah");
                }, 0.1f, "checkWave");
        }, 5.f, "firstWave");
}
void FirstMapScene::Wave9()
{
    scheduleOnce([this](float dt)
        {
            MonsterWave(NORMALMONSTER, 100, 20, 1.f); // ����ִ����������������߼�
            schedule([this](float dt)
                {
                    if (Monsters.CheckWave())
                    {
                        round++;
                        Wave10();
                        unschedule("checkWave");
                    }
                    CCLOG("hahahah");
                }, 0.1f, "checkWave");
        }, 5.f, "firstWave");
}
void FirstMapScene::Wave10()
{
    scheduleOnce([this](float dt)
        {
            MonsterWave(NORMALMONSTER, 100, 20, 1.f); // ����ִ����������������߼�
            schedule([this](float dt)
                {
                    if (Monsters.CheckWave())
                    {
                        win = 1;
                        isFirstMapWon = 1;
                        unschedule("checkWave");
                        return;
                    }
                    CCLOG("hahahah");
                }, 0.1f, "checkWave");
        }, 5.f, "firstWave");
}

