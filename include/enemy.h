#ifndef ENEMY_H
#define ENEMY_H

#include "combat.h"
#include "items.h"

typedef struct Enemy Enemy;

struct Enemy
{
    int life;
    int maxLife;
    int level;
    // int InCombo;    //pensando se coloco isso no ambiente tambem
    ItemID inventory[20];
    CombatWheel MyCombatWheel;
};

#endif