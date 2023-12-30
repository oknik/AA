
#include "MonsterManager.h"

void MonsterManager::AddMonster(Monster* monster)
{
    // Add the monster to the vector and addChild to the scene
    monsters.pushBack(monster);

}

void MonsterManager::UpdateMonsters(float dt)
{
    Vector<Monster*> monstersToRemove;  // 用于保存需要删除的怪物

    for (auto monster : monsters)
    {
        if (monster && monster->isValid())
        {
            monster->UpdateMonster(dt);
        }
        else
        {
            monstersToRemove.pushBack(monster);
        }
    }
    // 一次性删除需要删除的怪物
    for (auto monster : monstersToRemove)
    {
        monsters.eraseObject(monster);
        monster->removeFromParentAndCleanup(true);
    }
}

bool MonsterManager::CheckWave()
{
    if (monsters.empty())
    {
        return true;
       
    }
    else
    {
        return false;
    }
}

Vector<Monster*> MonsterManager::monsters;