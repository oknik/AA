
#include "MonsterManager.h"

void MonsterManager::AddMonster(Monster* monster)
{
    // Add the monster to the vector and addChild to the scene
    monsters.pushBack(monster);

}

void MonsterManager::UpdateMonsters(float dt)
{
    Vector<Monster*> monstersToRemove;  // ���ڱ�����Ҫɾ���Ĺ���

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
    // һ����ɾ����Ҫɾ���Ĺ���
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