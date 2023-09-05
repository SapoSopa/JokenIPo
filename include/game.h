#ifndef GAME_H
#define GAME_H

#include "items.h"
#include "combat.h"

typedef struct Player Player;
typedef struct Ambient Ambient;

struct Player {
    int life;
    int maxLife;
    int level;
    //int InCombo;    //pensando se coloco isso no ambiente tambem
    Item inventory[20];
    CombatWheel MyCombatWheel;
};

struct Ambient {
    int mapIdx;

    int round;
    int roundMax;
    
    float playerItemRandomChance;
    float enemyItemRandomChance;
    
    //maybe create a queue of ambient effects

    Player* player;
    //Enemy* enemy;

    Choice playerSelectedOption;
    Choice enemySelectedOption;

    Item UsedPlayerItem;
    Item UsedEnemyItem;

    int playerItemCooldown;
    int enemyItemCooldown;

};

int AmbientConstructor(Ambient *ambient);
int PlayerConstructor(Player *player);

 
int UpdateAmbient(); // update ambient

int doPlayerAction(Choice playerChoice); // do player action
int doEnemyAction(Choice playerChoice); // do enemy action

int doPlayerItemAction(Item item); // do player item action
int doEnemyItemAction(Item item); // do enemy item action


int LoadMap(int mapIdx); // load map from maps
int NextMap(); // load next map

/*
int LoadAmbient(); // load ambient from file
int SaveAmbient(); // save ambient in file

int LoadPlayer(); // load player from file
int SavePlayer(); // save player in file
*/

//int LoadEnemy();

int GetPlayerLife(); // return player life
int GetPlayerMaxLife(); // return player max life

int GetEnemyLife(); // return enemy life
int GetEnemyMaxLife(); // return enemy max life

#endif