/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "HelloWorldScene.h"
#include "MapSelectionScene.h"


cocos2d::Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    //创建“开始冒险”按钮
    auto StartItem = cocos2d::MenuItemImage::create(
        "StartNormal.png",
        "StartSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));    
    if (StartItem == nullptr ||StartItem->getContentSize().width <= 0 ||StartItem->getContentSize().height <= 0)
    {
        problemLoading("'StartNormal.png' and 'StartSelected.png'");
    }
    else
    {
        StartItem->setPosition(512, 450);
    }

    // create menu, it's an autorelease object
    auto menu = cocos2d::Menu::create(StartItem, NULL);
    menu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(menu, 1);

    StartItem->setCallback([=](cocos2d::Ref* sender) {
        cocos2d::AudioEngine::play2d("Select.mp3");// 播放音效
        auto mapSelectionScene = MapSelectionScene::createScene(); // 切换到地图选择场景
        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.0f, MapSelectionScene::createScene()));
        });

    //创建标签"Carrot Fantasy"
    auto label = cocos2d::Label::createWithTTF("Carrot Fantasy", "fonts/Marker Felt.ttf", 48);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));//标签的位置
        this->addChild(label, 1);
    }

    //创建背景图
    auto sprite = cocos2d::Sprite::create("BG.jpg");
    if (sprite == nullptr)
    {
        problemLoading("'BG.jpg'");
    }
    else
    {
        sprite->setScale(1000.0f / sprite->getContentSize().width, 600.0f / sprite->getContentSize().height);//设置图片大小，要跟运行框对应
        sprite->setPosition(cocos2d::Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(sprite, 0);
    }

    // 创建旋转的萝卜
    auto carrot = cocos2d::Sprite::create("Carrot_1.png");
    carrot->setPosition(cocos2d::Vec2(512, 100));
    this->addChild(carrot);
    float duration = 2.0f; // 旋转时间（秒）
    auto rotateAction = cocos2d::RotateBy::create(duration, 360); // 360度旋转
    carrot->runAction(cocos2d::RepeatForever::create(rotateAction)); // 永久重复旋转动作

    //添加背景音乐
    cocos2d::AudioEngine::play2d("BGM.mp3", true);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    cocos2d::Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
