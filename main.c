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

State GameState = Menu;

void mainWindow(){
	int monitor = GetCurrentMonitor();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280,1024, "JokenIPo"); //verificar pq 1280 e 720 dá seg fault - n dá mais ??
	int maxHeight = GetMonitorHeight(monitor) - 40;
	if (GetScreenHeight() > maxHeight)
		SetWindowSize(GetScreenWidth(), maxHeight);

    SetTargetFPS(60);
    //ToggleFullscreen();
}

void QuitApplication();
void UpdateMenu();
void UpdateGame();

int main () {
    mainWindow();
    SetActiveScreen(&mainMenu);
    Rectangle Player = {0, 0, 32, 64};
    tmx_map* map = GetMap(0);
    int currentMap = 0;
    UpdatePlayerPosition(map, &Player);
    // load somethings, temporaly here
    M_LoadMap();
    M_LoadTexture();
    // Main game loop
    while (!WindowShouldClose() && GameState != Quit)    // Detect window close button or ESC key
    {
        switch (GameState)
        {
        case Menu:
            UpdateMenu();
            break;
        case PlayOn:
            UpdateGame();
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        //UpdateScreen();

        //mainMenu();
        mapCanvas(currentMap, map);
        DrawRectangleRec(Player, RED);
    
        //FoundEnemyCanvas();
        //battleMenu();
    

        EndDrawing();
    }

    // De-Initialization
    UnloadResources();
    CloseWindow();                  
 
    return 0;
}

void QuitApplication() {
    GameState = Quit;
}

void UpdateMenu() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        QuitApplication();
    }

    if (IsKeyPressed(KEY_F11)){
        ToggleFullscreen();
    }
}

void UpdateGame() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        GameState = Menu;
    }
}
