#include <raylib.h>
#include <math.h>

#include "game.h"
#include "config.h"
#include "resourcesIdx.h"
#include "combat.h"
#include "items.h"
#include "screens.h"
#include "enemy.h"
#include "arena.h"

static Arena MainArena;
static ArenaPlayer MainPlayer;

static bool InBattle = false;

void StartBattle(ArenaEnemy *enemy) {
    ArenaConstructor(&MainArena, &MainPlayer, enemy);
    PlayerConstructor(&MainPlayer);

    InBattle = true;
    SetActiveScreen(&battleMenu);
}

void StartPlaying(){
    InBattle = False;
    PlayerControl(&Player, map);
    SetActiveScreen(NULL);
}

void StartTutorial() {
    InBattle = False;
    SetActiveScreen(&TutorialCanvas);
}

void DoPlayerChoice(Choice choice) {
    printf("Player choice: %d\n", choice);
    selectPlayerAction(&MainArena, choice);
}

void UpdateGameActions() {
    int result = 0;
    int roundResult = 0;
    if (InBattle) {
        UpdateArena(&MainArena, &result, &roundResult);
    }

    if (result != 0) {
        if (result == 1) {      // voltar para a tela do mapa e setar que o inimigo foi derrotado
            printf("Player won!\n");
            SetActiveScreen(&mainMenu);
        } else if (result == -1) {  // voltar para a tela do mapa e teletransportar para o inicio
            printf("Player lost!\n");
            SetActiveScreen(&mainMenu);
        }
        ResetArena();
    }
}

void ResetArena() {
    InBattle = false;
    SetActiveScreen(&mainMenu);

    ArenaConstructor(&MainArena, &MainPlayer, NULL);
    PlayerConstructor(&MainPlayer);
}