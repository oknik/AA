#ifndef __CARROT_H__
#define __CARROT_H__

#include "cocos2d.h"

class Carrot : public cocos2d::Sprite {
public:
    int hp; 

    virtual bool init();
    static Carrot* createCarrot();
    void updateCarrotSprite(); 
};

#endif // __CARROT_H__
