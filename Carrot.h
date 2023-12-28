#ifndef __CARROT_H__
#define __CARROT_H__

#include "cocos2d.h"

class Carrot : public cocos2d::Sprite {
public:
    int hp; 
    cocos2d::Label* HPLabel;

    virtual bool init();
    static Carrot* createCarrot();
    static cocos2d::Sprite* createHP();
    void updateCarrotSprite(); 
    cocos2d::Label* createHPLabel();
    void updateHPLabel();

    CREATE_FUNC(Carrot);

};

#endif // __CARROT_H__
