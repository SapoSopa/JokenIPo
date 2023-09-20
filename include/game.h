#ifndef GAME_H
#define GAME_H

#include "combat.h"
#include "items.h"
#include "enemy.h"
#include "arena.h"
#include "raylib.h"
#include "tmx.h"

typedef struct M_RoundResult RoundResult;

struct M_RoundResult {
    int gameResult;
    int roundResult;
    Choice playerChoice;
    Choice enemyChoice;
};

void StartBattle(ArenaEnemy *enemy);
void StartPlaying();
void StartTutorial();

bool IsRunning();
void SetRunning(bool running);

bool IsInBattle();
void SetInBattle(bool inBattle);

void PlayerControl(Rectangle *playerRect, tmx_map *map);
void EnvironmentControl(Rectangle *playerRect, tmx_map *map);

void DoPlayerChoice(Choice choice);

RoundResult UpdateGameActions();

void ResetArena();

#endif