#include <raylib.h>
#include <math.h>
#include <tmx.h>

#include "game.h"
#include "config.h"
#include "resourcesIdx.h"
#include "combat.h"
#include "items.h"
#include "screens.h"
#include "enemy.h"
#include "arena.h"
#include "include/canvas.h"
#include "load.h"

static Arena MainArena;
static ArenaPlayer MainPlayer;

static bool InBattle = false;
static bool Running = true;

bool IsRunning() {
    return Running;
}

void SetRunning(bool running) {
    Running = running;
}

bool IsInBattle() {
    return InBattle;
}

void SetInBattle(bool inBattle) {
    InBattle = inBattle;
}

void StartBattle(ArenaEnemy *enemy) {
    ArenaConstructor(&MainArena, &MainPlayer, enemy);
    PlayerConstructor(&MainPlayer);

    InBattle = true;
    SetActiveScreen(&battleMenu);
}

void StartPlaying(){
    InBattle = false;
    SetRunning(true);
    SetActiveScreen(NULL);
}

void StartTutorial() {
    InBattle = false;
    SetActiveScreen(&TutorialCanvas);
}

void DoPlayerChoice(Choice choice) {
    printf("Player choice: %d\n", choice);
    selectPlayerAction(&MainArena, choice);
}

RoundResult UpdateGameActions() {
    RoundResult result = {0, 0, 0, 0};
    if (InBattle) {
        UpdateArena(&MainArena, &result);
    }

    if (result.gameResult != 0) {
        if (result.gameResult == 1) {      // voltar para a tela do mapa e setar que o inimigo foi derrotado
            printf("Player won!\n");
            StartPlaying();
        } else if (result.gameResult == 2) {  // voltar para a tela do mapa e teletransportar para o inicio
            printf("Player lost!\n");
            ResetArena();
        }
    }
}

void ResetArena() {
    InBattle = false;
    SetActiveScreen(&mainMenu);

    ArenaConstructor(&MainArena, &MainPlayer, NULL);
    PlayerConstructor(&MainPlayer);
}

void PlayerControl(Rectangle *playerRect, tmx_map *map)
{
    Rectangle auxu = *playerRect;
    auxu.y -= 5;
    Rectangle auxd = *playerRect;
    auxd.y += 5;
    Rectangle auxl = *playerRect;
    auxl.x -= 5;
    Rectangle auxr = *playerRect;
    auxr.x += 5;
    if (IsKeyDown(KEY_UP) && !CheckObjgr(map, &auxu, "Paredes"))
    {
        playerRect->y -= 4; 
    }
    else if (IsKeyDown(KEY_UP) && CheckObjgr(map, &auxu, "Paredes"))
    {
        playerRect->y += 1;
    }
    if (IsKeyDown(KEY_DOWN) && !CheckObjgr(map, &auxd, "Paredes"))
    {
        playerRect->y += 4;
    }
    else if(IsKeyDown(KEY_DOWN) && CheckObjgr(map, &auxd, "Paredes"))
    {
        playerRect->y -= 1;
    }
    if (IsKeyDown(KEY_LEFT) && !CheckObjgr(map, &auxl, "Paredes"))
    {
        playerRect->x -= 4;
    }
    else if(IsKeyDown(KEY_LEFT) && CheckObjgr(map, &auxl, "Paredes"))
    {
        playerRect->x += 1;
    }
    if (IsKeyDown(KEY_RIGHT) && !CheckObjgr(map, &auxr, "Paredes"))
    {
        playerRect->x += 4;
    }
    else if(IsKeyDown(KEY_RIGHT) && CheckObjgr(map, &auxr, "Paredes"))
    {
        playerRect->x -= 1;
    }
}

void EnvironmentControl(Rectangle *playerRect, tmx_map *map) {
    if (!map || !playerRect)
        return;

    EnemyList *enemies = GetEnemies();
    mapCanvas(map);
    DrawCenteredTexture(*GetTexture(Texture_Player), playerRect->x, playerRect->y, WHITE);
    if(CheckObjgr(map, playerRect, "Inimigos"))
    {   
        printf("Enemy found!\n");
        if(!EnemyDefeated(map, playerRect, enemies))
        {
            DrawText("Press E to interact", playerRect->x-10, playerRect->y-10, 20, WHITE);
            if (IsKeyPressed(KEY_E))
            {
                SetActiveScreen(&FoundEnemyCanvas);
                SetInBattle(true);
                SetRunning(false);
            }
        }
        else if(CheckObjgr(map, playerRect, "Portas"))
        {
            DrawText("Press E to enter", playerRect->x - 10, playerRect->y-10, 20, WHITE);
            if (IsKeyPressed(KEY_E))
            {
                UpdateMap(map, playerRect);
            }
        }
        
        } 
}