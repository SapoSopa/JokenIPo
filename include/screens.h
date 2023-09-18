#pragma once
#include <stdio.h>

static void (*activeScreen)() = NULL;

void SetActiveScreen(void (*screen)());
void UpdateScreen();

void FoundEnemyCanvas();

void mainMenu();

void mapCanvas();

void startBattleCanvas();

void battleMenu();