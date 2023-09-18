#ifndef ENEMY_H
#define ENEMY_H

#include "config.h"
#include "combat.h"
#include "items.h"

typedef struct Enemy Enemy;

struct Enemy
{
    int life;
    int maxLife;
    int level;
    // int InCombo;    //pensando se coloco isso no ambiente tambem
    ItemID inventory[MAX_INV_SIZE];
    CombatWheel MyCombatWheel;
};

#endif