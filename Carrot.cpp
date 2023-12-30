#include"Carrot.h"
#include"cocos2d.h"
//#include"FirstMapScene.h"

bool Carrot::init() {
    if (!Sprite::initWithFile("test/Carrot_2.png")) {
        return false;
    }
    hp = 10;
    HPLabel = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("%d", hp), "fonts/Marker Felt.ttf", 10);
    if (HPLabel) {
        HPLabel->setPosition(cocos2d::Vec2(800, 520));
        HPLabel->setTextColor(cocos2d::Color4B::BLACK);
    }

    this->schedule([this](float dt) {
        this->updateCarrotSprite();
        this->updateHPLabel();
        }, 0.1f, "update_carrot_hp");

    return true;
}

Carrot* Carrot::createCarrot() {
    auto carrot = new Carrot();
    if (carrot && carrot->init()) {
        carrot->autorelease();
        return carrot;
    }
    CC_SAFE_DELETE(carrot);
    return nullptr;
}

cocos2d::Sprite* Carrot::createHP() {
    auto hp = new Carrot();
    if (hp && hp->initWithFile("test/HP.png")) {
        hp->autorelease();
        return hp;
    }
    CC_SAFE_DELETE(hp);
    return nullptr;
}

cocos2d::Label* Carrot::createHPLabel() {
    auto label = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("%d", hp), "fonts/Marker Felt.ttf", 10);
    if (!label) {
        CCLOG("Error creating HP Label");
    }
    return label;
}

void Carrot::updateCarrotSprite() {
    if (hp >= 10) {
        this->setTexture("test/Carrot_2.png");
    }
    if (hp <= 9 && hp >= 7) {
        this->setTexture("test/Carrot_3.png");
    }
    if (hp <= 6 && hp >= 4) {
        this->setTexture("test/Carrot_4.png");
    }
    if (hp <= 3) {
        this->setTexture("test/Carrot_5.png");
    }
    if (hp <= 1)
        hp = 1;
}

void Carrot::updateHPLabel() {
    if (HPLabel) {
        HPLabel->setString(cocos2d::StringUtils::format("%d", hp));
    }
}




