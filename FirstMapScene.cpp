#include"audio/include/AudioEngine.h"
#include"Data.h"
#include"HelloWorldScene.h"
#include"MapSelectionScene.h"
#include"FirstMapScene.h"
#include"Object.h"
#include"Tower.h"
#include<vector>

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

cocos2d::Scene* FirstMapScene::createScene() {
    auto scene = FirstMapScene::create();
    return scene;
}

void FirstMapScene::backToMain(cocos2d::Ref* sender) {
    isFirstMapWon = true;
    int selectId = cocos2d::AudioEngine::play2d("test/Select.mp3", false);//这里的true or false是循环的意思
    this->schedule([=](float dt) {
        if (cocos2d::AudioEngine::getState(selectId) != cocos2d::AudioEngine::AudioState::PLAYING) {
            cocos2d::AudioEngine::stopAll();
            this->unschedule("checkAudioFinished");
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.0f, HelloWorld::createScene()));// 在音频播放完毕后执行切换场景的操作
        }
        }, "checkAudioFinished");
}

void FirstMapScene::pause(cocos2d::Ref* sender) {
    if (Director::getInstance()->isPaused()) {
        Director::getInstance()->resume(); // 恢复场景的运行
    }
    else {
        Director::getInstance()->pause(); // 暂停场景的运行
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

    scheduleOnce([this, myCarrot = carrot, road](float dt)
        {
            MonsterWave(FASTMONSTER, 70, 10, 1.f, myCarrot, road);
        }, 0.f, "firstWave");

    scheduleOnce([this, myCarrot = carrot, road](float dt)
        {
            MonsterWave(BIGMONSTER, 70, 3, 3.f, myCarrot, road);
        }, 2.f, "secondWave");
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
            this->addChild(menu,12); 
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

cocos2d::ui::Button* FirstMapScene::createSelectButton() {
    auto mainButton = cocos2d::ui::Button::create("tower/blank.png");

    auto bottleButton = cocos2d::ui::Button::create("tower/pickBottle.png");
    bottleButton->setPosition(Vec2(-25, 50));
    bottleButton->setVisible(false);

    auto shitButton = cocos2d::ui::Button::create("tower/pickShit.png");
    shitButton->setPosition(Vec2(25, 50));
    shitButton->setVisible(false);

    auto snowButton = cocos2d::ui::Button::create("tower/pickSnow.png");
    snowButton->setPosition(Vec2(75, 50));
    snowButton->setVisible(false);

    mainButton->addChild(bottleButton);
    mainButton->addChild(shitButton);
    mainButton->addChild(snowButton);

    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (bottleButton->isVisible() || shitButton->isVisible() || snowButton->isVisible()) {
            bottleButton->setVisible(false);
            shitButton->setVisible(false);
            snowButton->setVisible(false);
        }
        return false;
        };

    mainButton->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, mainButton);

    mainButton->addClickEventListener([=](Ref* sender) {
        if (bottleButton->isVisible() || shitButton->isVisible() || snowButton->isVisible()) {
            bottleButton->setVisible(false);
            shitButton->setVisible(false);
            snowButton->setVisible(false);
        }
        else {
            bottleButton->setVisible(true);
            shitButton->setVisible(true);
            snowButton->setVisible(true);
        }
        });

    return mainButton;
}

bool FirstMapScene::init() {
    if (!Scene::init()) {
        return false;
    }

    //这是一个监听器
    label = cocos2d::Label::createWithTTF("Mouse Position: (0, 0)", "fonts/arial.ttf", 24);
    label->setPosition(cocos2d::Vec2(300, 300)); // 设置位置
    this->addChild(label, 1);
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(FirstMapScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    cocos2d::AudioEngine::stopAll();
    cocos2d::AudioEngine::play2d("test/PlayBGM.mp3", true);

    auto sprite = cocos2d::Sprite::create("test/SelectBG.png");
    if (sprite == nullptr)
    {
        problemLoading("'test/SelectBG.png'");
    }
    else
    {
        sprite->setScale(1000.0f / sprite->getContentSize().width, 600.0f / sprite->getContentSize().height);//设置图片大小，要跟运行框对应
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
        path->setScale(1000.0f / path->getContentSize().width, 600.0f / path->getContentSize().height);//设置图片大小，要跟运行框对应
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

    auto roundLabel = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("%d      10 rounds", round), "fonts/Marker Felt.ttf", 24);
    if (roundLabel) {
        roundLabel->setPosition(cocos2d::Vec2(540, 575));
        this->addChild(roundLabel);
    }
    else {
        CCLOG("Error creating Label");
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
        auto menu = cocos2d::Menu::create(BackItem, nullptr); // 创建菜单并添加返回按钮
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu);
    }
    else {
        CCLOG("Failed to load back button"); // 如果创建失败，输出错误信息
    }

    auto button1 = createSelectButton();
    button1->setPosition(cocos2d::Vec2(252,372));
    this->addChild(button1, 1);

    auto button2 = createSelectButton();
    button2->setPosition(cocos2d::Vec2(252, 317));
    this->addChild(button2, 1);

    auto button3 = createSelectButton();
    button3->setPosition(cocos2d::Vec2(252, 262));
    this->addChild(button3, 1);

    auto button4 = createSelectButton();
    button4->setPosition(cocos2d::Vec2(252, 152));
    this->addChild(button4, 1);

    auto button5 = createSelectButton();
    button5->setPosition(cocos2d::Vec2(185, 480));
    this->addChild(button5, 1);

    auto button6 = createSelectButton();
    button6->setPosition(cocos2d::Vec2(308, 480));
    this->addChild(button6, 1);

    auto button7 = createSelectButton();
    button7->setPosition(cocos2d::Vec2(370, 425));
    this->addChild(button7, 1);

    auto button8 = createSelectButton();
    button8->setPosition(cocos2d::Vec2(370, 325));
    this->addChild(button8, 1);

    auto button9 = createSelectButton();
    button9->setPosition(cocos2d::Vec2(370, 272));
    this->addChild(button9, 1);

    auto button10 = createSelectButton();
    button10->setPosition(cocos2d::Vec2(410, 225));
    this->addChild(button10, 1);

    auto button11 = createSelectButton();
    button11->setPosition(cocos2d::Vec2(460, 225));
    this->addChild(button11, 1);

    auto button12 = createSelectButton();
    button12->setPosition(cocos2d::Vec2(510, 225));
    this->addChild(button12, 1);

    auto button13 = createSelectButton();
    button13->setPosition(cocos2d::Vec2(410, 100));
    this->addChild(button13, 1);

    auto button14 = createSelectButton();
    button14->setPosition(cocos2d::Vec2(460, 100));
    this->addChild(button14, 1);

    auto button15 = createSelectButton();
    button15->setPosition(cocos2d::Vec2(510, 100));
    this->addChild(button15, 1);

    auto button16 = createSelectButton();
    button16->setPosition(cocos2d::Vec2(625, 100));
    this->addChild(button16, 1);

    auto button17 = createSelectButton();
    button17->setPosition(cocos2d::Vec2(685, 100));
    this->addChild(button17, 1);

    auto button18 = createSelectButton();
    button18->setPosition(cocos2d::Vec2(630, 325));
    this->addChild(button18, 1);

    auto button19 = createSelectButton();
    button19->setPosition(cocos2d::Vec2(630, 272));
    this->addChild(button19, 1);

    auto button20 = createSelectButton();
    button20->setPosition(cocos2d::Vec2(685, 480));
    this->addChild(button20, 1);

    auto button21 = createSelectButton();
    button21->setPosition(cocos2d::Vec2(735, 480));
    this->addChild(button21, 1);

    auto button22 = createSelectButton();
    button22->setPosition(cocos2d::Vec2(735, 375));
    this->addChild(button22, 1);

    auto button23 = createSelectButton();
    button23->setPosition(cocos2d::Vec2(735, 325));
    this->addChild(button23, 1);

    auto button24 = createSelectButton();
    button24->setPosition(cocos2d::Vec2(735, 275));
    this->addChild(button24, 1);

    auto button25 = createSelectButton();
    button25->setPosition(cocos2d::Vec2(735, 155));
    this->addChild(button25, 1);

    auto button26 = createSelectButton();
    button26->setPosition(cocos2d::Vec2(735, 105));
    this->addChild(button26, 1);

    auto tree1 = Tree::createTree();
    tree1->setPosition(cocos2d::Vec2(194, 374));
    this->addChild(tree1);

    auto tree2 = Tree::createTree();
    tree2->setPosition(cocos2d::Vec2(260, 205));
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
    ice7->setPosition(cocos2d::Vec2(570, 100));
    this->addChild(ice7);

    auto bigIce1 = BigIce::createBigIce();
    bigIce1->setPosition(cocos2d::Vec2(335, 100));
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


    //this->schedule(CC_SCHEDULE_SELECTOR(FirstMapScene::updateFail), 0.1f);

    auto hpButton = cocos2d::MenuItemImage::create("test/Update.png", "test/Update.png", [=](cocos2d::Ref* sender) {
        if (money >= 500) {
            carrot->hp += 1;
            money -= 500;
            carrot->updateCarrotSprite();//修改萝卜图案
            moneyLabel->setString(cocos2d::StringUtils::format("%d", money));//修改moneyLable
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

    std::vector<Path> road;
    road.push_back(Path(RIGHT, 118.f));
    road.push_back(Path(DOWN, 260.f));
    road.push_back(Path(RIGHT, 370.f));
    road.push_back(Path(UP, 260.f));
    road.push_back(Path(RIGHT, 118.f));

    scheduleOnce([this, myCarrot = carrot, road](float dt)
        {
            MonsterWave(FASTMONSTER, 70, 10, 1.f, myCarrot, road);
        }, 0.f, "firstWave");

    scheduleOnce([this, myCarrot = carrot, road](float dt)
        {
            MonsterWave(BIGMONSTER, 70, 3, 3.f, myCarrot, road);
        }, 2.f, "secondWave");

    return true;
}

void FirstMapScene::MonsterWave(const int type, const float blood, const int count, const float inr,
    Carrot* carrot, std::vector<Path> road)
{
    if (type == NORMALMONSTER)
    {
        for (int i = 0; i < count; i++)
        {
            NormalMonster* monster = NormalMonster::create(blood, INITX1, INITY1);
            monster->SetCarrot(carrot);
            this->addChild(monster, 5);
            monster->Move(road, float(inr * i));
        }
    }
    if (type == FASTMONSTER)
    {
        for (int i = 0; i < count; i++)
        {
            FastMonster* monster = FastMonster::create(blood, INITX1, INITY1);
            monster->SetCarrot(carrot);
            this->addChild(monster, 5);
            monster->Move(road, float(inr * i));
            //monster->retain();
        }
    }
    if (type == BIGMONSTER)
    {
        for (int i = 0; i < count; i++)
        {
            BigMonster* monster = BigMonster::create(blood, INITX1, INITY1);
            monster->SetCarrot(carrot);
            this->addChild(monster, 5);
            monster->Move(road, float(inr * i));
        }
    }
}


void FirstMapScene::checkWave(float dt)
{

}
