#include"audio/include/AudioEngine.h"
#include"Data.h"
#include"HelloWorldScene.h"
#include"FirstMapScene.h"
#include"Object.h"
#include"Carrot.h"
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

bool FirstMapScene::init() {
    if (!Scene::init()) {
        return false;
    }


    //这是一个监听器
    /*label = cocos2d::Label::createWithTTF("Mouse Position: (0, 0)", "fonts/arial.ttf", 24);
    label->setPosition(cocos2d::Vec2(300, 300)); // 设置位置
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

    auto BackItem = cocos2d::MenuItemImage::create(
        "test/BackNormal.png",
        "test/BackSelected.png",
        CC_CALLBACK_1(FirstMapScene::backToMain, this));
    if (BackItem) {
        BackItem->setPosition(cocos2d::Vec2(100, 100));
        auto menu = cocos2d::Menu::create(BackItem, nullptr); // 创建菜单并添加返回按钮
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu);
    }
    else {
        CCLOG("Failed to load back button"); // 如果创建失败，输出错误信息
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

    auto carrot = Carrot::createCarrot();
    carrot->setPosition(cocos2d::Vec2(810, 485));
    this->addChild(carrot);

    auto HP = cocos2d::Sprite::create("test/HP.png");
    HP->setPosition(cocos2d::Vec2(810, 520));
    this->addChild(HP);

    auto HPLabel = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("%d", carrot->hp), "fonts/Marker Felt.ttf", 10);
    if (HPLabel == nullptr) {
        CCLOG("Error creating HP Label");
    }
    HPLabel->setPosition(cocos2d::Vec2(800, 520));
    HPLabel->setTextColor(cocos2d::Color4B::BLACK);
    this->addChild(HPLabel, 1); 

    auto hpButton = cocos2d::MenuItemImage::create("test/Update.png", "test/Update.png", [=](cocos2d::Ref* sender) {
        if (money >= 500) {
            carrot->hp += 1;
            money -= 500;
            carrot->updateCarrotSprite();//修改萝卜图案
            HPLabel->setString(cocos2d::StringUtils::format("%d", carrot->hp));
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


    scheduleOnce([this, carrot, road](float dt)
        {
            MonsterWave(FASTMONSTER, 70, 10, 1.f, carrot, road);
        }, 0.f, "firstWave");

    scheduleOnce([this, carrot, road](float dt)
        {
            MonsterWave(BIGMONSTER, 70, 3, 3.f, carrot, road);
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