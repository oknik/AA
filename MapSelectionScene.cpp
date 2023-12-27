#include"audio/include/AudioEngine.h"
#include"Data.h"
#include"HelloWorldScene.h"
#include"MapSelectionScene.h"
#include"FirstMapScene.h"
#include"SecondMapScene.h"


cocos2d::Scene* MapSelectionScene::createScene() {
    cocos2d::AudioEngine::play2d("test/Select.mp3");// 播放音效
    auto scene = MapSelectionScene::create();
    return scene;
}

void MapSelectionScene::backToMain(cocos2d::Ref* sender) {
    int selectId = cocos2d::AudioEngine::play2d("test/Select.mp3", false);//这里的true or false是循环的意思
    this->schedule([=](float dt) {
        if (cocos2d::AudioEngine::getState(selectId) != cocos2d::AudioEngine::AudioState::PLAYING) {
            cocos2d::AudioEngine::stopAll(); 
            this->unschedule("checkAudioFinished");
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.0f, HelloWorld::createScene()));// 在音频播放完毕后执行切换场景的操作
        }
        }, "checkAudioFinished");
}

void MapSelectionScene::gotoFirstMap(cocos2d::Ref* sender) {
    int selectId = cocos2d::AudioEngine::play2d("test/Select.mp3", false);//这里的true or false是循环的意思
    this->schedule([=](float dt) {
        if (cocos2d::AudioEngine::getState(selectId) != cocos2d::AudioEngine::AudioState::PLAYING) {
            cocos2d::AudioEngine::stopAll();
            this->unschedule("checkAudioFinished");
            auto firstMapScene = FirstMapScene::createScene();
            firstMapScene->setTag(111);
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.0f, FirstMapScene::createScene()));
        }
        }, "checkAudioFinished");
}

void MapSelectionScene::gotoSecondMap(cocos2d::Ref* sender) {
    int selectId = cocos2d::AudioEngine::play2d("test/Select.mp3", false);//这里的true or false是循环的意思
    this->schedule([=](float dt) {
        if (cocos2d::AudioEngine::getState(selectId) != cocos2d::AudioEngine::AudioState::PLAYING) {
            cocos2d::AudioEngine::stopAll();
            this->unschedule("checkAudioFinished");
            auto secondMapScene = SecondMapScene::createScene();
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.0f, SecondMapScene::createScene()));
        }
        }, "checkAudioFinished");
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MapSelectionScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto sprite = cocos2d::Sprite::create("test/SelectBG.png");
    if (sprite) {
        sprite->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
        sprite->setScale(1000.0f / sprite->getContentSize().width, 600.0f / sprite->getContentSize().height);//设置图片大小，要跟运行框对应
        this->addChild(sprite);
    }
    else {
        CCLOG("Failed to load sprite");// 如果创建失败，输出错误信息
    }

    auto label = cocos2d::Label::createWithTTF("Map Selection", "fonts/Marker Felt.ttf", 48);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(500, 550);//标签的位置
        this->addChild(label, 1);
    }

    //创建返回按钮
    auto BackItem = cocos2d::MenuItemImage::create(
        "test/BackNormal.png",
        "test/BackSelected.png",
        CC_CALLBACK_1(MapSelectionScene::backToMain, this));
    if (BackItem) {
        BackItem->setPosition(cocos2d::Vec2(100, 100));
        auto menu = cocos2d::Menu::create(BackItem, nullptr); // 创建菜单并添加返回按钮
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu);
    }
    else {
        CCLOG("Failed to load back button"); // 如果创建失败，输出错误信息
    }

    //创建地图按钮
    auto FirstMapButton = cocos2d::MenuItemImage::create(
        "test/Map1Normal.png",   
        "test/Map1Selected.jpg", 
        CC_CALLBACK_1(MapSelectionScene::gotoFirstMap, this)); 

    if (FirstMapButton) {
        FirstMapButton->setPosition(cocos2d::Vec2(250, 300));
        auto menu = cocos2d::Menu::create(FirstMapButton, nullptr);
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu);
    }
    else {
        CCLOG("Failed to load map button"); // 如果创建按钮失败，输出错误信息
    }

    auto SecondMapButton = cocos2d::MenuItemImage::create(
        "test/Map2Normal.png", // 解锁状态的图片
        "test/Map2Selected.jpg", // 点击时状态的图片
        CC_CALLBACK_1(MapSelectionScene::gotoSecondMap, this));

    if (!isFirstMapWon) {
        // 如果第一个地图未被赢得，第二个地图按钮保持被锁定状态
        SecondMapButton->setEnabled(false); // 禁用按钮
        SecondMapButton->setOpacity(128); // 降低透明度以显示被锁定的状态
    }

    if (SecondMapButton) {
        SecondMapButton->setPosition(cocos2d::Vec2(750, 300));
        auto menu = cocos2d::Menu::create(SecondMapButton, nullptr);
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu);
    }
    else {
        CCLOG("Failed to load map button"); // 如果创建按钮失败，输出错误信息
    }

    return true;
}
