#include"Tower.h"
#include"cocos2d.h"

USING_NS_CC;

#define BOTTLE 0
#define SHIT 1
#define SNOW 2

/*************************һ�Ѹ����������ȼ������Բ���*************************/
const std::string chooseTower[3] = { "pickBottle.png","pickshit.png","picksnow.png" };//��������ʱ��Ҫ��ͼƬ
const std::string Towers[3] = { "bottle","shit","snow" };//-----------------------------������������
const std::string bases[3] = { "bottlebase","shitbase","snowbase" };//----------------------���������ĵ���
const int construct_costs[3] = { 100,120,160 };//-----------------------------------------������������Ľ��
const int upgrade_costs[3][2] = { {180,220},
                                  {220,260},
                                  {260,320} };//----------------------------------------������������Ľ��
const int attack_powers[3] = { 10,20,30 };//--------------------------------------------���ȼ�����ʱ��ǿ��
const int attack_ranges[3] = { 10,20,30 };//--------------------------------------------���ȼ������ķ�Χ

bool Tower::init(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
        return false;
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