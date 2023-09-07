#include "include/items.h"
#include "include/game.h"
#include "include/enemy.h"
#include "include/combat.h"
#include "include/load.h"

#include "raylib.h"

typedef int State;
enum GameStates {
    Loading,
    Menu,
    Paused,
    PlayOn,
    GameOver,
    Quit
};

State GameState = Loading;

void mainWindow(){
    InitWindow(1280,720,"JokenIPo");
    SetTargetFPS(60);
    //ToggleFullscreen();
}

int main () {
    mainWindow();
    InitAudioDevice();

    while (!WindowShouldClose() && GameState != Quit){
        BeginDrawing();
        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    UnloadAll();
    CloseWindow();

    return 0;
}