#ifndef ARENA_H
#define ARENA_H

#include "combat.h"
#include "enemy.h"
#include "items.h"

typedef struct Player Player;
typedef struct Arena Arena;

struct Player
{
    int life;
    int maxLife;
    int level;
    // int InCombo;    //pensando se coloco isso no arena tambem
    ItemID inventory[20];
    CombatWheel MyCombatWheel;
};

struct Arena
{
    int mapIdx;

    int round;
    int roundMax;

    float playerItemRandomChance;
    float enemyItemRandomChance;

    // maybe create a queue of arena effects

    Player *player;
    Enemy *enemy;

    Choice playerSelectedOption;
    Choice enemySelectedOption;

    int UsedPlayerItemIdx;
    int UsedEnemyItemIdx;

    int playerItemCooldown;
    int enemyItemCooldown;
};

int ArenaConstructor(Arena *ambient, Player *player, Enemy *enemy);
int PlayerConstructor(Player *player);

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

/*
int LoadArena(); // load arena file
int SaveArena(); // save arena file

int LoadPlayer(); // load player from file
int SavePlayer(); // save player in file
*/

// int LoadEnemy();

int GetPlayerLife();    // return player life
int GetPlayerMaxLife(); // return player max life

int GetEnemyLife();    // return enemy life
int GetEnemyMaxLife(); // return enemy max life

#endif