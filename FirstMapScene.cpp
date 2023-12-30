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
    round = 1;
    win = 0;

    this->removeChildByName("FailSprite");
    this->removeChildByName("TryAgainMenu");
    this->removeChildByName("SelectMenu");
    this->removeAllMonster();

    
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

    //这是一个监听器
    /*label = cocos2d::Label::createWithTTF("Mouse Position: (0, 0)", "fonts/arial.ttf", 24);
    label->setPosition(cocos2d::Vec2(300, 300)); // 设置位置
    this->addChild(label, 1);
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(FirstMapScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);*/

    cocos2d::AudioEngine::stopAll();
    cocos2d::AudioEngine::play2d("test/PlayBGM.mp3", true);

    auto sprite = cocos2d::Sprite::create("test/SelectBG.png");//0层
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

    auto path = cocos2d::Sprite::create("test/Path1.png");//0层
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

    auto upBoard = cocos2d::Sprite::create("test/UpBoard.png");//0层
    if (upBoard == nullptr)
    {
        problemLoading("'test/UpBoard.png'");
    }
    else
    {
        upBoard->setPosition(cocos2d::Vec2(500, 571));
        this->addChild(upBoard, 0);
    }

    auto upBoard2 = cocos2d::Sprite::create("test/UpBoard2.png");//0层
    if (upBoard == nullptr)
    {
        problemLoading("'test/UpBoard2.png'");
    }
    else
    {
        upBoard2->setPosition(cocos2d::Vec2(537, 571));
        this->addChild(upBoard2, 0);
    }

    auto moneyLabel = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("%d", money), "fonts/Marker Felt.ttf", 24);//0层
    if (moneyLabel) {
        moneyLabel->setPosition(cocos2d::Vec2(200, 575));
        this->addChild(moneyLabel, 0);
    }
    else {
        CCLOG("Error creating Label");
    }

    auto roundLabel = createRoundLabel();//0层
    if (roundLabel) {
        roundLabel->setPosition(cocos2d::Vec2(540, 575));
        this->addChild(roundLabel, 0);
    }
    else {
        CCLOG("Error creating Round Label");
    }

    auto speedUpItem1 = MenuItemImage::create("test/Speed_1.png", "test/Speed_1.png");
    auto speedUpItem2 = MenuItemImage::create("test/Speed_2.png", "test/Speed_2.png");
    auto speedUp = MenuItemToggle::createWithCallback(CC_CALLBACK_1(FirstMapScene::changeSpeed, this), speedUpItem1, speedUpItem2, nullptr);
    if (speedUp) {
        speedUp->setPosition(Vec2(730, 570));
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








    enum GridType { _BOOTLE, _SHIT, _SNOW, _ICE, _BIGICE, _TREE, _HOUSE, _ICECREAM, _NO, _YES };

    // 假设这是一个表示不同格子类型的二维数组
    int gridMap[9][17] = {
        { _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO},
        { _NO, _NO, _NO, _NO, _NO, _BIGICE, _BIGICE, _YES, _YES, _ICE, _YES, _YES, _YES, _NO, _NO, _NO, _NO},
        { _NO, _NO, _YES, _YES, _YES, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _YES, _YES, _YES, _NO, _NO},
        { _NO, _NO, _YES, _YES, _TREE, _NO, _ICECREAM, _YES, _YES, _BIGICE, _BIGICE, _NO, _TREE, _YES, _YES, _NO, _NO},
        { _NO, _NO, _YES, _YES, _YES, _NO, _YES, _YES, _ICE, _YES, _YES, _NO, _YES, _YES, _YES, _NO, _NO},
        { _NO, _NO, _YES, _TREE, _YES, _NO, _ICE, _ICE, _YES, _ICE, _YES, _NO, _YES, _TREE, _YES, _NO, _NO},
        { _NO, _NO, _YES, _NO, _NO, _NO, _YES, _YES, _YES, _HOUSE, _HOUSE, _NO, _NO, _NO, _YES, _NO, _NO},
        { _NO, _NO, _YES, _YES, _ICE, _YES, _ICE, _YES, _YES, _HOUSE, _HOUSE, _YES, _YES, _YES, _YES, _NO, _NO},
        { _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO, _NO},
    };

    // 循环创建不同类型的格子
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 17; col++) {
            // 计算每个格子的位置
            float posX = col * 60 + 25;   // 格子的中心 X 坐标
            float posY = row * 68 + 20; // 格子的中心 Y 坐标
            if (row == 1 && col == 5) {
                col++;
            }
            if (row == 1 && col == 6) {
                posX += 30;
            }
            if (row == 3 && col == 9) {
                col++;
            }
            if (row == 3 && col == 10) {
                posX += 30;
            }
            if (row == 6 && col == 9) {
                col++;
            }
            if (row == 6 && col == 10) {
                col++;
            }
            if (row == 7 && col == 9) {
                col++;
            }
            if (row == 7 && col == 10) {
                posX += 30;
                posY -= 40;
            }

            // 创建精灵并添加到场景中
            std::string filename;
            switch (gridMap[row][col]) {
            case _ICE:
                filename = "test/Ice.png";
                break;
            case _BIGICE:
                filename = "test/BigIce.png";
                break;
            case _ICECREAM:
                filename = "test/Icecream.png";
                break;
            case _TREE:
                filename = "test/Tree.png";
                break;
            case _HOUSE:
                filename = "test/House.png";
                break;

            }
            Sprite* gridSprite = Sprite::create(filename);
            if (gridSprite) {
                gridSprite->setPosition(Vec2(posX, posY));
                this->addChild(gridSprite);
            }
        }
    }

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 touchPos = touch->getLocation();
        Label* label = Label::createWithTTF(StringUtils::format("Touch Pos: (%.2f, %.2f)", touchPos.x, touchPos.y), "fonts/arial.ttf", 50);
        if (label) {
            label->setPosition(Vec2(100, 100)); // 设置 Label 的位置
            this->addChild(label, 10); // 将 Label 添加到场景中
        }
        int col = (touchPos.x) / 60;
        int row = (touchPos.y) / 68;
        GridType type = static_cast<GridType>(gridMap[row][col]);
        if (type == _YES) {
            auto blank = Sprite::create("tower/blank.png");
            if (blank == nullptr) {
                problemLoading("'blank.png'");
            }
            else {
                this->addChild(blank, 1);
            }

            auto pickBottle = Sprite::create("tower/pickBottle.png");
            if (pickBottle == nullptr) {
                problemLoading("'pickbottle.png'");
            }
            else {
                this->addChild(pickBottle, 1);
            }
            pickBottle->setScale(0.6);

            auto pickShit = Sprite::create("tower/pickShit.png");
            if (pickShit == nullptr) {
                problemLoading("'pickshit.png'");
            }
            else {
                this->addChild(pickShit, 1);
            }
            pickShit->setScale(0.6);

            auto pickSnow = Sprite::create("tower/pickSnow.png");
            if (pickSnow == nullptr) {
                problemLoading("'picksnow.png'");
            }
            else {
                this->addChild(pickSnow, 1);
            }
            pickSnow->setScale(0.6);

            blank->setPosition(Vec2(col * 60 + 25, row * 68 + 20));
            pickBottle->setPosition(Vec2(col * 60 + 25 - 45, row * 68 + 20 + 45));
            pickShit->setPosition(Vec2(col * 60 + 25, row * 68 + 20 + 45));
            pickSnow->setPosition(Vec2(col * 60 + 25 + 45, row * 68 + 20 + 45));

            // 创建 Sprite 的点击监听器
            auto spriteListener = EventListenerTouchOneByOne::create();
            spriteListener->setSwallowTouches(true);

            // 监听点击事件
            spriteListener->onTouchBegan = [=](Touch* touch, Event* event) {
                auto target = static_cast<Sprite*>(event->getCurrentTarget());
                Vec2 choice = touch->getLocation();

                if (target->getBoundingBox().containsPoint(choice)) {
                    if (target == pickBottle) {
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
                    else if (target == pickShit) {
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
                    else if (target == pickSnow) {
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
                    return true;
                }
                return false;
                };

            _eventDispatcher->addEventListenerWithSceneGraphPriority(spriteListener->clone(), pickBottle);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(spriteListener->clone(), pickShit);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(spriteListener->clone(), pickSnow);
            return true;
        }
        return false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}



















