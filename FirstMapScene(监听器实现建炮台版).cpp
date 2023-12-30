#include"audio/include/AudioEngine.h"
#include"FirstMapScene.h"
#include"Object.h"
#include"Carrot.h"
#include"Tower.h"
#include"Bottle.h"

#define BOTTLE 0
#define SHIT 1
#define SNOW 2

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

bool FirstMapScene::init() {
    if (!Scene::init()) {
        return false;
    }

    //播放音乐
    AudioEngine::stopAll();
    AudioEngine::play2d("PlayBGM.mp3", true);

    //背景图
    auto sprite = Sprite::create("SelectBG.png");
    if (sprite == nullptr)
    {
        problemLoading("'SelectBG.png'");
    }
    else
    {
        sprite->setPosition(Vec2(500, 300));
        this->addChild(sprite, 0);
    }

    //路径图
    auto path = Sprite::create("Path1.png");
    if (path == nullptr)
    {
        problemLoading("'Path1.png'");
    }
    else
    {
        path->setScale(1000.0f / path->getContentSize().width, 600.0f / path->getContentSize().height);//设置图片大小，要跟运行框对应
        path->setPosition(Vec2(500, 300));
        this->addChild(path, 0);
    }

    //顶部状态栏
    auto upBoard = Sprite::create("UpBoard.png");
    if (upBoard == nullptr)
    {
        problemLoading("'UpBoard.png'");
    }
    else
    {
        upBoard->setPosition(Vec2(500, 571));
        this->addChild(upBoard, 0);
    }

    auto upBoard2 = Sprite::create("UpBoard2.png");
    if (upBoard == nullptr)
    {
        problemLoading("'UpBoard2.png'");
    }
    else
    {
        upBoard2->setPosition(Vec2(537, 571));
        this->addChild(upBoard2, 0);
    }

    //金币图标
    auto moneyLabel = Label::createWithTTF(StringUtils::format("%d", money), "fonts/Marker Felt.ttf", 24);
    if (moneyLabel) {
        moneyLabel->setPosition(Vec2(200, 575));
        this->addChild(moneyLabel);
    }
    else {
        CCLOG("Error creating Label");
    }

    auto roundLabel = Label::createWithTTF(StringUtils::format("%d      10 rounds", round), "fonts/Marker Felt.ttf", 24);
    if (roundLabel) {
        roundLabel->setPosition(Vec2(540, 575));
        this->addChild(roundLabel);
    }
    else {
        CCLOG("Error creating Label");
    }

    //各种障碍物
    auto tree1 = Tree::createTree();
    tree1->setPosition(Vec2(194, 374));
    this->addChild(tree1);

    auto tree2 = Tree::createTree();
    tree2->setPosition(Vec2(265, 225));
    this->addChild(tree2);

    auto tree3 = Tree::createTree();
    tree3->setPosition(Vec2(736, 225));
    this->addChild(tree3);

    auto tree4 = Tree::createTree();
    tree4->setPosition(Vec2(809, 374));
    this->addChild(tree4);

    auto ice1 = Ice::createIce();
    ice1->setPosition(Vec2(245, 475));
    this->addChild(ice1);

    auto ice2 = Ice::createIce();
    ice2->setPosition(Vec2(365, 475));
    this->addChild(ice2);

    auto ice3 = Ice::createIce();
    ice3->setPosition(Vec2(365, 380));
    this->addChild(ice3);

    auto ice4 = Ice::createIce();
    ice4->setPosition(Vec2(415, 380));
    this->addChild(ice4);

    auto ice5 = Ice::createIce();
    ice5->setPosition(Vec2(512, 280));
    this->addChild(ice5);

    auto ice6 = Ice::createIce();
    ice6->setPosition(Vec2(589, 380));
    this->addChild(ice6);

    auto ice7 = Ice::createIce();
    ice7->setPosition(Vec2(589, 100));
    this->addChild(ice7);

    auto bigIce1 = BigIce::createBigIce();
    bigIce1->setPosition(Vec2(365, 100));
    this->addChild(bigIce1);

    auto bigIce2 = BigIce::createBigIce();
    bigIce2->setPosition(Vec2(591, 225));
    this->addChild(bigIce2);

    auto icecream = Icecream::createIcecream();
    icecream->setPosition(Vec2(365, 225));
    this->addChild(icecream);

    auto house = House::createHouse();
    house->setPosition(Vec2(591, 435));
    this->addChild(house);

    auto carrot = Carrot::createCarrot();
    carrot->setPosition(Vec2(810, 485));
    this->addChild(carrot);

    auto HP = Sprite::create("HP.png");
    HP->setPosition(Vec2(810, 520));
    this->addChild(HP);

    //萝卜升级按钮
    auto HPLabel = Label::createWithTTF(StringUtils::format("%d", carrot->hp), "fonts/Marker Felt.ttf", 10);
    if (HPLabel == nullptr) {
        CCLOG("Error creating HP Label");
    }
    HPLabel->setPosition(Vec2(800, 520));
    HPLabel->setTextColor(Color4B::BLACK);
    this->addChild(HPLabel, 1);

    auto hpButton = MenuItemImage::create("Update.png", "Update.png", [=](Ref* sender) {
        if (money >= 500) {
            carrot->hp += 1;
            money -= 500;
            carrot->updateCarrotSprite();//修改萝卜图案
            HPLabel->setString(StringUtils::format("%d", carrot->hp));
            moneyLabel->setString(StringUtils::format("%d", money));//修改moneyLable
            AudioEngine::play2d("Select.mp3", false);
        }
        else {
            AudioEngine::play2d("Wrong.mp3", false);
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

    //定义有效的操作范围（？？？）
    Rect validArea = Rect(100, 100, 800, 400);  //有效范围，在范围内可以放置炮塔

    //创建选择炮台时的定位白框
    auto blank = Sprite::create("blank.png");
    if (blank == nullptr) {
        problemLoading("'blank.png'");
    }
    else {
        this->addChild(blank, 0);
        blank->setVisible(false);
    }
    blank->setScale(0.6); //重新调整白框大小

    //创建炮台选择界面
    auto pickBottle = Sprite::create("pickbottle.png");
    if (pickBottle == nullptr) {
        problemLoading("'pickbottle.png'");
    }
    else {
        this->addChild(pickBottle, 0);
        pickBottle->setVisible(false);
    }

    auto pickShit = Sprite::create("pickshit.png");
    if (pickShit == nullptr) {
        problemLoading("'pickshit.png'");
    }
    else {
        this->addChild(pickShit, 0);
        pickShit->setVisible(false);
    }
    pickShit->setScale(0.6); //重新调整大小

    auto pickSnow = Sprite::create("picksnow.png");
    if (pickSnow == nullptr) {
        problemLoading("'picksnow.png'");
    }
    else {
        this->addChild(pickSnow, 0);
        pickSnow->setVisible(false);
    }
    pickSnow->setScale(0.6); //重新调整大小

//这里开始是新改的，覆盖之前的即可！

 //监听器,跟踪鼠标位置，在点击时显示选择炮台的定位白框
 auto listener = EventListenerTouchOneByOne::create();
 listener->onTouchBegan = [blank, pickBottle, pickShit, pickSnow, validArea, this](Touch* touch, Event* event) {
     Vec2 touchPos = touch->getLocation();
     if (!blank->isVisible()) { //当选择框不可见时
         if (validArea.containsPoint(touchPos)) { //若在范围内，显示炮台选项
             blank->setPosition(Vec2(touchPos.x, touchPos.y));
             blank->setVisible(true);
             pickBottle->setPosition(Vec2(touchPos.x, touchPos.y + 45));
             pickBottle->setVisible(true);
             pickShit->setPosition(Vec2(touchPos.x - 45, touchPos.y + 45));
             pickShit->setVisible(true);
             pickSnow->setPosition(Vec2(touchPos.x + 45, touchPos.y + 45));
             pickSnow->setVisible(true);
         }
         else {  //若不在范围内，播放错误音效，不显示选项
             blank->setVisible(false);
             pickBottle->setVisible(false);
             pickShit->setVisible(false);
             pickSnow->setVisible(false);
             AudioEngine::play2d("Wrong.mp3", false);
             return false;
         }
     }
     else {//当选择框可见时
         Vec2 choice = touch->getLocation();
         if (pickBottle->getBoundingBox().containsPoint(choice)) {  //选中瓶子炮
             Vec2 blankPos = blank->getPosition();
             auto bottle = Tower::create(blankPos,BOTTLE);
             if (bottle == nullptr) {
                 CCLOG("failed to construct a bottle");
             }
             else {
                 bottle->setPosition(blankPos);
                 this->addChild(bottle, 2);
             }
         }
         if (pickShit->getBoundingBox().containsPoint(choice)) {  //选中便便
             Vec2 blankPos = blank->getPosition();
             auto shit = Tower::create(blankPos,SHIT);
             if (shit == nullptr) {
                 CCLOG("failed to construct a shit");
             }
             else {
                 shit->setPosition(blankPos);
                 this->addChild(shit, 2);
             }
         }
         if (pickSnow->getBoundingBox().containsPoint(choice)) {  //选中雪花
             Vec2 blankPos = blank->getPosition();
             auto snow = Tower::create(blankPos,SNOW);
             if (snow == nullptr) {
                 CCLOG("failed to construct a snow");
             }
             else {
                 snow->setPosition(blankPos);
                 this->addChild(snow, 2);
                 snow->setScale(0.8);
             }
         }
         blank->setVisible(false);
         pickBottle->setVisible(false);
         pickShit->setVisible(false);
         pickSnow->setVisible(false);
     }
     return true;
     };
 _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
