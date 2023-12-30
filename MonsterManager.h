#pragma once
#include "Monster.h"


class MonsterManager;



class MonsterManager : public Node
{
private:
    static Vector<Monster*> monsters;

public:


    ~MonsterManager() { monsters.clear(); }

    void AddMonster(Monster* monster);

    static void UpdateMonsters(float dt);

    bool CheckWave();
};