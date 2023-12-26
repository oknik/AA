#include"Carrot.h"

bool Carrot::init() {
    if (!Sprite::init()) {
        return false;
    }

    schedule([this](float dt)
        {
            this->updateCarrotSprite();
        }, 0.1f, "update_carrot");

    return true;
}

Carrot* Carrot::createCarrot() {
    auto carrot = new Carrot();
    if (carrot && carrot->initWithFile("test/Carrot_2.png")) {
        carrot->autorelease();
        carrot->hp = 10;
        return carrot;
    }
    CC_SAFE_DELETE(carrot);
    return nullptr;
}

void Carrot::updateCarrotSprite() {
    if (hp >= 10) {
        this->setTexture("test/Carrot_2.png");
    }
    if (hp <= 9 && hp >= 6) {
        this->setTexture("test/Carrot_3.png");
    }
    if (hp <= 5 && hp >= 3) {
        this->setTexture("test/Carrot_4.png");
    }
    if (hp <= 2) {
        this->setTexture("test/Carrot_5.png");
    }
}






