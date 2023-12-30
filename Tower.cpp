#include"Tower.h"
#include"cocos2d.h"


USING_NS_CC;



/*************************һ�Ѹ����������ȼ������Բ���*************************/
const std::string chooseTower[3] = { "tower/pickBottle.png","tower/pickshit.png","tower/picksnow.png" };//��������ʱ��Ҫ��ͼƬ
const std::string Towers[3] = { "tower/bottle","tower/shit","tower/snow" };//-----------------------------������������
const std::string bases[3] = { "tower/bottlebase","tower/shitbase","tower/snowbase" };//----------------------���������ĵ���
const std::string bullets[3] = { "tBottle-6.png","tower/TShit - hd","tower/TSnow - hd.plist" };

const int construct_costs[3] = { 100,120,160 };//-----------------------------------------������������Ľ��
const int upgrade_costs[3][2] = { {180,220},
                                  {220,260},
                                  {260,320} };//----------------------------------------������������Ľ��
const int attack_powers[3] = { 10,20,30 };//--------------------------------------------���ȼ�����ʱ��ǿ��
const int attack_ranges[3] = { 10,20,30 };//--------------------------------------------���ȼ������ķ�Χ


bool Tower::init(const std::string& filename)
{
    int tag = 1;
    if (!Sprite::initWithFile(filename))
        return false;

    schedule([this](float dt)
        {
            //updateTower();
        }, 0.1f, "update_tower");


    return true;
}

Tower* Tower::construct(Vec2 position, int choice)
{
    //���������������ͼƬ��Ӧ
    Tower* tower = new Tower();

    

    //�ɹ�����һ��������������г�ʼ��
    if (tower && tower->init(chooseTower[choice])) {
        tower->base->setTexture(bases[choice]);//--------------------��ʼ����̨����
        tower->level = 0;//------------------------------------------��ʼ���ȼ�Ϊ0��
        tower->tag = choice;//---------------------------------------��ʼ��������ǩ����������ƿ��/���/ѩ��
        tower->construct_cost = construct_costs[choice];//-----------��ʼ����������������
        tower->upgrade_cost = upgrade_costs[choice][tower->level];//-��ʼ����������������
        tower->attack_power = attack_powers[tower->level];//---------��ʼ������ǿ��
        tower->attack_range = attack_ranges[tower->level];//---------��ʼ��������Χ
        tower->base->setPosition(position);//------------------------��������ָ��λ��
        tower->setPosition(position);//------------------------------��̨����ָ��λ��

        
        return tower;
    }
    return nullptr;
}

void Tower::upgrade(Tower* tower)
{
    tower->level++;//-------------------------------------------------��������+1
    tower->setTexture(Towers[tag] + std::to_string(tag) + ".png");//------��������ͼ��
    tower->upgrade_cost = upgrade_costs[tower->tag][tower->level];//--������������������
    tower->attack_power = attack_powers[tower->level];//--------------���¹���ǿ��
    tower->attack_range = attack_ranges[tower->level];//--------------���¹�����Χ
}


//void Tower::attackAnimation()
//{
//    Vector<SpriteFrame*> images;
//    images.pushBack(SpriteFrame::create("tower/tSnow-1.png", Rect(0, 0, 250, 250)));
//    images.pushBack(SpriteFrame::create("tower/tSnow-2.png", Rect(0, 0, 280, 280)));
//    images.pushBack(SpriteFrame::create("tower/tSnow-3.png", Rect(0, 0, 310, 310)));
//    images.pushBack(SpriteFrame::create("tower/tSnow-4.png", Rect(0, 0, 330, 330)));
//    images.pushBack(SpriteFrame::create("tower/tSnow-5.png", Rect(0, 0, 340, 340)));
//    images.pushBack(SpriteFrame::create("tower/tSnow-6.png", Rect(0, 0, 390, 390)));
//    images.pushBack(SpriteFrame::create("tower/tSnow-7.png", Rect(0, 0, 400, 400)));
//
//}



void Tower::attackAnimation()
{
    Vector<SpriteFrame*> images;
    images.pushBack(SpriteFrame::create("tower/tSnow-1.png", Rect(0, 0, 250, 250)));
    images.pushBack(SpriteFrame::create("tower/tSnow-2.png", Rect(0, 0, 280, 280)));
    images.pushBack(SpriteFrame::create("tower/tSnow-3.png", Rect(0, 0, 310, 310)));
    images.pushBack(SpriteFrame::create("tower/tSnow-4.png", Rect(0, 0, 330, 330)));
    images.pushBack(SpriteFrame::create("tower/tSnow-5.png", Rect(0, 0, 340, 340)));
    images.pushBack(SpriteFrame::create("tower/tSnow-6.png", Rect(0, 0, 390, 390)));
    images.pushBack(SpriteFrame::create("tower/tSnow-7.png", Rect(0, 0, 400, 400)));
}

Monster* Tower::getClosestMonster(const Vector<Monster*>& monsters) {
    Monster* closestMonster = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for (Monster* monster : monsters) {
        float distance = this->getPosition().distance(monster->getPosition());

        if (distance < attack_range && distance < closestDistance) {
            closestMonster = monster;
            closestDistance = distance;
        }
    }
    return closestMonster;
}

void Tower::shoot(Monster* targetMonster) {
    if (targetMonster) {
        bullet = Sprite::create("tower/tBottle-6.png");
        bullet->setPosition(this->getPosition());
        if (targetMonster)
        {
            Vec2 direction = targetMonster->getPosition() - this->getPosition();
            direction.normalize();
            // ��һ�����ٶ���׷��Ŀ��
            this->setPosition(this->getPosition() + direction * bullet_speed);
        }
        this->getParent()->addChild(bullet, 10);  // ��ӵ����ڵ㣬ע�����ú��ʵ�Z��㼶
    }
}

void Tower::updateTower(Vector<Monster*>monsters)
{
    
    Monster* targetMonster = getClosestMonster(monsters);
    rotateToMonster(targetMonster);
    shoot(targetMonster);
}

void Tower::rotateToMonster(Monster* targetMonster) 
{
    if (targetMonster) 
    {
        Vec2 direction = targetMonster->getPosition() - this->getPosition();
        float angle = CC_RADIANS_TO_DEGREES(direction.getAngle());
        this->setRotation(-angle);
    }
}