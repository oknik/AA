#include"Tower.h"
#include"cocos2d.h"

USING_NS_CC;

#define BOTTLE 0
#define SHIT 1
#define SNOW 2

const std::string chooseTower[3] = { "pickBottle.png","pickshit.png","picksnow.png" };
const std::string bases[3]={"bottlebase","shitbase","snowcase"};

bool Tower::init()
{
    if (!Sprite::init())
        return false;

}
      
Tower* Tower::construct(Vec2 position, int choice)
{
    //���������������ͼƬ��Ӧ
    auto tower = Sprite::create(chooseTower[choice]);
    if (tower == nullptr) { //����ʧ��
        CCLOG("Construction Failed");
        return nullptr;
    }
}