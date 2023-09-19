#ifndef ENEMY_H
#define ENEMY_H

#include "config.h"
#include "combat.h"
#include "items.h"

typedef struct M_Enemy ArenaEnemy;

struct M_Enemy
{
    int life;
    int maxLife;
    ItemID inventory[MAX_INV_SIZE];
    CombatWheel MyCombatWheel;
};

int EnemyChooseAction(ArenaEnemy *enemy);

#endif