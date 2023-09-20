#pragma once

#include <raylib.h>
#include <stdio.h>

static void (*activeScreen)() = NULL;

void SetActiveScreen(void (*screen)());
void UpdateScreen();

void FoundEnemyCanvas();

void mainMenu();

void TutorialCanvas();

void mapCanvas(tmx_map *map);

void startBattleCanvas();

void battleMenu();

void Creditos();