#include"Tower.h"
#include"cocos2d.h"


USING_NS_CC;



/*************************一堆各炮塔、各等级的特性参数*************************/
const std::string chooseTower[3] = { "tower/pickBottle.png","tower/pickshit.png","tower/picksnow.png" };//建造炮塔时需要的图片
const std::string Towers[3] = { "tower/bottle","tower/shit","tower/snow" };//-----------------------------储存炮塔名称
const std::string bases[3] = { "tower/bottlebase","tower/shitbase","tower/snowbase" };//----------------------各个炮塔的底座
const std::string bullets[3] = { "tBottle-6.png","tower/TShit - hd","tower/TSnow - hd.plist" };

const int construct_costs[3] = { 100,120,160 };//-----------------------------------------建造炮塔所需的金币
const int upgrade_costs[3][2] = { {180,220},
                                  {220,260},
                                  {260,320} };//----------------------------------------升级炮塔所需的金币
const int attack_powers[3] = { 10,20,30 };//--------------------------------------------各等级攻击时的强度
const int attack_ranges[3] = { 10,20,30 };//--------------------------------------------各等级攻击的范围


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
    //建造炮塔，编号与图片对应
    Tower* tower = new Tower();

    

    //成功建造一个炮塔，对其进行初始化
    if (tower && tower->init(chooseTower[choice])) {
        tower->base->setTexture(bases[choice]);//--------------------初始化炮台底座
        tower->level = 0;//------------------------------------------初始化等级为0级
        tower->tag = choice;//---------------------------------------初始化炮塔标签，代表它是瓶子/便便/雪花
        tower->construct_cost = construct_costs[choice];//-----------初始化炮塔建造所需金币
        tower->upgrade_cost = upgrade_costs[choice][tower->level];//-初始化升级炮塔所需金币
        tower->attack_power = attack_powers[tower->level];//---------初始化攻击强度
        tower->attack_range = attack_ranges[tower->level];//---------初始化攻击范围
        tower->base->setPosition(position);//------------------------底座置于指定位置
        tower->setPosition(position);//------------------------------炮台置于指定位置

        
        return tower;
    }
    return nullptr;
}

void Tower::upgrade(Tower* tower)
{
    tower->level++;//-------------------------------------------------炮塔级数+1
    tower->setTexture(Towers[tag] + std::to_string(tag) + ".png");//------重置炮塔图像
    tower->upgrade_cost = upgrade_costs[tower->tag][tower->level];//--更新升级炮塔所需金币
    tower->attack_power = attack_powers[tower->level];//--------------更新攻击强度
    tower->attack_range = attack_ranges[tower->level];//--------------更新攻击范围
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
            // 在一定的速度下追踪目标
            this->setPosition(this->getPosition() + direction * bullet_speed);
        }
        this->getParent()->addChild(bullet, 10);  // 添加到父节点，注意设置合适的Z轴层级
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