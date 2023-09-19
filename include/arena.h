#ifndef ARENA_H
#define ARENA_H

#include "config.h"
#include "combat.h"
#include "enemy.h"
#include "items.h"

typedef struct M_Player ArenaPlayer;
typedef struct Arena Arena;

struct M_Player
{
    int life;
    int maxLife;
    // int InCombo;    //pensando se coloco isso no arena tambem
    ItemID inventory[MAX_INV_SIZE];
    CombatWheel MyCombatWheel;
};

struct Arena
{
    int round;
    int roundMax;

    // maybe create a queue of arena effects

    ArenaPlayer *player;
    ArenaEnemy *enemy;

    Choice playerSelectedOption;
    Choice enemySelectedOption;

    int UsedPlayerItemIdx;
    int UsedEnemyItemIdx;

    int playerItemCooldown;
    int enemyItemCooldown;
};

int ArenaConstructor(Arena *ambient, ArenaPlayer *player, ArenaEnemy *enemy);
int PlayerConstructor(ArenaPlayer *player);

int nextRound(Arena *arena);   // next round
int UpdateArena(Arena *arena); // update ambient

int selectPlayerAction(Arena *arena, Choice playerChoice); // do player action
int selectEnemyAction(Arena *arena, Choice playerChoice);  // do enemy action

int selectPlayerItem(Arena *arena, int ItemInvIdx); // select player item
int selectEnemyItem(Arena *arena, int ItemInvIdx);  // select enemy item

int doPlayerItemAction(Arena *arena); // do player item action
int doEnemyItemAction(Arena *arena);  // do enemy item action

int doCombat(Arena *arena); // do combat

int LoadMap(int mapIdx); // load map from maps
int NextMap();           // load next map

// int LoadEnemy();

int GetPlayerLife();    // return player life
int GetPlayerMaxLife(); // return player max life

int GetEnemyLife();    // return enemy life
int GetEnemyMaxLife(); // return enemy max life

#endif