#include"Tower.h"
#include"cocos2d.h"

USING_NS_CC;

#define BOTTLE 0
#define SHIT 1
#define SNOW 2

/*************************一堆各炮塔、各等级的特性参数*************************/
const std::string chooseTowers[3] = { "pickBottle.png","pickshit.png","picksnow.png" };//建造炮塔时需要的图片
const std::string Towers[3] = { "bottle","shit","snow" };//-----------------------------储存炮塔名称
const std::string bases[3]={"bottlebase.png","shitbase.png","snowbase.png"};//----------------------各个炮塔的底座
const int construct_costs[3] = {100,120,160};//-----------------------------------------建造炮塔所需的金币
const int upgrade_costs[3][2] = { {180,220},
                                  {220,260},
                                  {260,320} };//----------------------------------------升级炮塔所需的金币
const int attack_powers[3] = { 10,20,30 };//--------------------------------------------各等级攻击时的强度
const int attack_ranges[3] = { 10,20,30 };//--------------------------------------------各等级攻击的范围

/**************************************************
* position:目标的建造位置
* choice:BOTTLE  SHIT  SNOW选择建造哪个
***************************************************/
Tower* Tower::create(Vec2 position, int choice) {
    Tower* tower = new (std::nothrow) Tower();
    if (tower && tower->init(position, choice)) {
        tower->autorelease();
        return tower;
    }
    CC_SAFE_DELETE(tower);
    return nullptr;
}

bool Tower::init(Vec2 position, int choice) {
    if (!Sprite::initWithFile(Towers[choice] + std::to_string(level+1) + ".png")) {
        return false;
    }

    // 初始化操作
    this->base = Sprite::create(bases[choice]);//---------------------生成底座
    if (this->base) {//底座生成成功再做初始化操作
        this->addChild(this->base);

        this->level = 0;//--------------------------------------------初始化等级为0级
        this->tag = choice;//-----------------------------------------宏定义编号，保存炮塔类别
        this->construct_cost = construct_costs[choice];//-------------建造所需的金币
        this->upgrade_cost = upgrade_costs[choice][this->level];//----升级所需的金币
        this->attack_power = attack_powers[this->level];//------------初始化攻击力
        this->attack_range = attack_ranges[this->level];//------------初始化攻击范围
        this->base->setPosition(position);  //------------------------设置底座位置
        this->setPosition(position);//--------------------------------设置炮塔位置

        return true;
    }

    return false;
}

void Tower::upgrade(Tower* tower)
{  
    tower->level++;//-------------------------------------------------炮塔级数+1
    tower->setTexture(Towers[tag]+std::to_string(tag)+".png");//------重置炮塔图像
    tower->upgrade_cost = upgrade_costs[tower->tag][tower->level];//--更新升级炮塔所需金币
    tower->attack_power = attack_powers[tower->level];//--------------更新攻击强度
    tower->attack_range = attack_ranges[tower->level];//--------------更新攻击范围
}
