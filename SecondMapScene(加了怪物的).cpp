#include"audio/include/AudioEngine.h"
#include"SecondMapScene.h"
#include"Object.h"
#include"Carrot.h"
#include "Monster.h"




static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

cocos2d::Scene* SecondMapScene::createScene() {
    auto scene = SecondMapScene::create();
    return scene;
}

bool SecondMapScene::init() {
    if (!Scene::init()) {
        return false;
    }


    //这是一个监听器
    label = cocos2d::Label::createWithTTF("Mouse Position: (0, 0)", "fonts/arial.ttf", 24);
    label->setPosition(cocos2d::Vec2(300, 300)); // 设置位置
    this->addChild(label, 1);
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(SecondMapScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);



    cocos2d::AudioEngine::stopAll();
    cocos2d::AudioEngine::play2d("test/PlayBGM.mp3", true);

    auto sprite = cocos2d::Sprite::create("test/SelectBG.png");
    if (sprite == nullptr)
    {
        problemLoading("'SelectBG.png'");
    }
    else
    {
        sprite->setScale(1000.0f / sprite->getContentSize().width, 600.0f / sprite->getContentSize().height);//设置图片大小，要跟运行框对应
        sprite->setPosition(cocos2d::Vec2(500, 300));
        this->addChild(sprite, 0);
    }

    auto path = cocos2d::Sprite::create("test/Path2.png");
    if (path == nullptr)
    {
        problemLoading("'Path2.png'");
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
        problemLoading("'UpBoard.png'");
    }
    else
    {
        upBoard->setPosition(cocos2d::Vec2(500, 571));
        this->addChild(upBoard, 0);
    }

    auto upBoard2 = cocos2d::Sprite::create("test/UpBoard2.png");
    if (upBoard == nullptr)
    {
        problemLoading("'UpBoard2.png'");
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

    auto tree1 = Tree::createTree();
    tree1->setPosition(cocos2d::Vec2(795, 270));
    this->addChild(tree1);

    auto tree2 = Tree::createTree();
    tree2->setPosition(cocos2d::Vec2(795, 219));
    this->addChild(tree2);

    auto tree3 = Tree::createTree();
    tree3->setPosition(cocos2d::Vec2(795, 170));
    this->addChild(tree3);

    auto tree4 = Tree::createTree();
    tree4->setPosition(cocos2d::Vec2(840, 322));
    this->addChild(tree4);

    auto bigTree1 = BigTree::createBigTree();
    bigTree1->setPosition(cocos2d::Vec2(215, 435));
    this->addChild(bigTree1);

    auto bigTree2 = BigTree::createBigTree();
    bigTree2->setPosition(cocos2d::Vec2(400, 435));
    this->addChild(bigTree2);

    auto bigTree3 = BigTree::createBigTree();
    bigTree3->setPosition(cocos2d::Vec2(655, 435));
    this->addChild(bigTree3);

    auto ice1 = Ice::createIce();
    ice1->setPosition(cocos2d::Vec2(380, 170));
    this->addChild(ice1);

    auto ice2 = Ice::createIce();
    ice2->setPosition(cocos2d::Vec2(380, 220));
    this->addChild(ice2);

    auto ice3 = Ice::createIce();
    ice3->setPosition(cocos2d::Vec2(430, 170));
    this->addChild(ice3);

    auto ice4 = Ice::createIce();
    ice4->setPosition(cocos2d::Vec2(560, 100));
    this->addChild(ice4);

    auto ice5 = Ice::createIce();
    ice5->setPosition(cocos2d::Vec2(680, 100));
    this->addChild(ice5);

    auto stone = Stone::createStone();
    stone->setPosition(cocos2d::Vec2(550, 350));
    this->addChild(stone);

    auto icecream1 = Icecream::createIcecream();
    icecream1->setPosition(cocos2d::Vec2(140, 220));
    this->addChild(icecream1);

    auto icecream2 = Icecream::createIcecream();
    icecream2->setPosition(cocos2d::Vec2(140, 365));
    this->addChild(icecream2);

    auto icecream3 = Icecream::createIcecream();
    icecream3->setPosition(cocos2d::Vec2(675, 310));
    this->addChild(icecream3);

    auto house1 = House::createHouse();
    house1->setPosition(cocos2d::Vec2(290, 265));
    this->addChild(house1);

    auto house2 = House::createHouse();
    house2->setPosition(cocos2d::Vec2(540, 187));
    this->addChild(house2);

    auto carrot = Carrot::createCarrot();
    carrot->setPosition(cocos2d::Vec2(755, 485));
    this->addChild(carrot);

    auto HP = cocos2d::Sprite::create("test/HP.png");
    HP->setPosition(cocos2d::Vec2(755, 520));
    this->addChild(HP);

    auto HPLabel = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("%d", carrot->hp), "fonts/Marker Felt.ttf", 10);
    if (HPLabel == nullptr) {
        CCLOG("Error creating HP Label");
    }
    HPLabel->setPosition(cocos2d::Vec2(745, 520));
    HPLabel->setTextColor(cocos2d::Color4B::BLACK);
    this->addChild(HPLabel, 1);

    auto hpButton = cocos2d::MenuItemImage::create("test/Update.png", "test/Update.png", [=](cocos2d::Ref* sender) {
        if (money >= 500) {
            carrot->hp += 1;
            money -= 500;
            carrot->updateCarrotSprite();//修改萝卜图案
            HPLabel->setString(cocos2d::StringUtils::format("%d", carrot->hp));
            moneyLabel->setString(cocos2d::StringUtils::format("%d", money));//修改moneyLable
            cocos2d::AudioEngine::play2d("Select.mp3", false);
        }
        else {
            cocos2d::AudioEngine::play2d("test/Wrong.mp3", false);
        }
        });
    if (hpButton) {
        hpButton->setPosition(cocos2d::Vec2(795, 470));
        auto menu = cocos2d::Menu::create(hpButton, nullptr);
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu);
        auto Label = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("500"), "fonts/Marker Felt.ttf", 10);
        if (Label) {
            Label->setPosition(cocos2d::Vec2(798, 455));
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




    schedule(CC_SCHEDULE_SELECTOR(SecondMapScene::update), 1.0f);

    //std::vector<Path> road;
    //road.push_back(Path(LEFT, 250.f));
    //road.push_back(Path(UP, 60.f));
    //road.push_back(Path(LEFT, 60.f));
    //road.push_back(Path(UP, 200.f));
    //road.push_back(Path(RIGHT, 185.f));
    //road.push_back(Path(DOWN, 60.f));
    //road.push_back(Path(RIGHT, 245.f));
    //road.push_back(Path(DOWN, 140.f));
    //road.push_back(Path(RIGHT, 120.f));
    //road.push_back(Path(UP, 290.f));

    
    //monster.Move(road);

    return true;
}

//
//void SecondMapScene::MonsterWave(const int type, const float blood, const int count, const float inr,
//    Carrot* carrot, std::vector<Path> road)
//{
//    if (type == NORMALMONSTER)
//    {
//        for (int i = 0; i < count; i++)
//        {
//            NormalMonster* monster = NormalMonster::create(90, INITX2, INITY2);
//            monster->SetCarrot(carrot);
//            this->addChild(monster, 5);
//            monster->Move(road, float(inr * i));
//        }
//    }
//    if (type == FASTMONSTER)
//    {
//        for (int i = 0; i < count; i++)
//        {
//            FastMonster* monster = FastMonster::create(90, INITX2, INITY2);
//            monster->SetCarrot(carrot);
//            this->addChild(monster, 5);
//            monster->Move(road, float(inr * i));
//            //monster->retain();
//        }
//    }
//    if (type == BIGMONSTER)
//    {
//        for (int i = 0; i < count; i++)
//        {
//            BigMonster* monster = BigMonster::create(90, INITX2, INITY2);
//            monster->SetCarrot(carrot);
//            this->addChild(monster, 5);
//            monster->Move(road, float(inr * i));
//        }
//    }
//}