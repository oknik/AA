#include"Tower.h"
#include"cocos2d.h"

USING_NS_CC;

#define BOTTLE 0
#define SHIT 1
#define SNOW 2

/*************************一堆各炮塔、各等级的特性参数*************************/
const std::string chooseTower[3] = { "pickBottle.png","pickshit.png","picksnow.png" };//建造炮塔时需要的图片
const std::string Towers[3] = { "bottle","shit","snow" };//-----------------------------储存炮塔名称
const std::string bases[3] = { "bottlebase","shitbase","snowbase" };//----------------------各个炮塔的底座
const int construct_costs[3] = { 100,120,160 };//-----------------------------------------建造炮塔所需的金币
const int upgrade_costs[3][2] = { {180,220},
                                  {220,260},
                                  {260,320} };//----------------------------------------升级炮塔所需的金币
const int attack_powers[3] = { 10,20,30 };//--------------------------------------------各等级攻击时的强度
const int attack_ranges[3] = { 10,20,30 };//--------------------------------------------各等级攻击的范围

bool Tower::init(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
        return false;
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