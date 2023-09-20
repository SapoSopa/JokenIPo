#ifndef ENEMY_H
#define ENEMY_H

#include "config.h"
#include "combat.h"
#include "items.h"
#include "raylib.h"
#include "tmx.h"

typedef struct M_Enemy ArenaEnemy;
typedef struct M_EnemyList EnemyList;

struct M_Enemy
{
    int MyTexure;
    int life;
    int maxLife;
    ItemID inventory[MAX_INV_SIZE];
    CombatWheel MyCombatWheel;
};

struct M_EnemyList {
    char *name;
    bool defeated;
};

void StartEnemies();

ArenaEnemy* GetEnemy(int enemyIdx);

int EnemyChooseAction(ArenaEnemy *enemy);

bool EnemyDefeated(tmx_map *map, Rectangle *playerRect, EnemyList *enemies);

int EnemyId(tmx_map *map, Rectangle *playerRect, EnemyList *enemies);

void SetDefeatEnemy(int id);

EnemyList* GetEnemies();

#endif