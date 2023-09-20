#include "raylib.h"
#include <tmx.h>
#include "include/items.h"
#include "include/game.h"
#include "include/enemy.h"
#include "include/combat.h"
#include "include/load.h"
#include "include/screens.h"
#include "include/map.h"
#include "include/resourcesIdx.h"
#include "include/canvas.h"
#include "include/audio.h"

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

    InitAudioDevice();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280,1024, "JokenIPo"); 
	int maxHeight = GetMonitorHeight(monitor) - 40;
	if (GetScreenHeight() > maxHeight)
		SetWindowSize(GetScreenWidth(), maxHeight);

    SetTargetFPS(60);
}


void QuitApplication();
void UpdateMenu();
void UpdateGame();
void UpdateMovement();


int main () {
    mainWindow();
    SetActiveScreen(&mainMenu);
    
    // load somethings, temporaly here
    M_LoadMap();
    M_LoadTexture();
    StartEnemies();

    // Player setup
    Rectangle Player = {0, 0, 32, 64};
    SetCurrentMap(GetMap(0));
    tmx_map* map = GetCurrentMap();
    UpdatePlayerPosition(map, &Player);
    SetRunning(false);
    
    
    // Main game loop
    while (!WindowShouldClose() && GameState != Quit)    // Detect window close button or ESC key
    {
        // Update
        switch (GameState)
        {
        case Menu:
            UpdateMenu();
            break;
        case PlayOn:
            UpdateGame();
            break;
        }
        
        PlayerControl(&Player, map);
        BeginDrawing();
        ClearBackground(BLACK);

        UpdateScreen();
        
        if(IsRunning())
        {
            EnvironmentControl(&Player, map);
        }
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
