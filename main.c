#include "raylib.h"
#include <tmx.h>
#include "include/items.h"
#include "include/game.h"
#include "include/enemy.h"
#include "include/combat.h"
#include "include/load.h"
#include "include/screens.h"

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
    InitWindow(1280,1024, "JokenIPo"); //verificar pq 1280 e 720 dá seg fault
    SetTargetFPS(60);
    //ToggleFullscreen();
}

int main () {
    mainWindow();

    // load somethings, temporaly here
    M_LoadMap();
    M_LoadTexture();
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        //mainMenu();
        mapCanvas();
        //FoundEnemyCanvas();
        //battleMenu();
        EndDrawing();
    }
    UnloadResources();
    CloseWindow();                  
 
    return 0;
}