#ifndef GAME_H
#define GAME_H

#include "combat.h"
#include "items.h"
#include "enemy.h"
#include "arena.h"

void StartBattle(ArenaEnemy *enemy);
void StartPlaying();
void StartTutorial();

void DoPlayerChoice(Choice choice);

void UpdateGameActions();

void ResetArena();

#endif