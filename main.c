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
    InitWindow(1280,720, "JokenIPo"); //verificar pq 1280 e 720 dá seg fault - n dá mais ??
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

    // load somethings, temporaly here
    M_LoadMap();
    M_LoadTexture();

    Rectangle Player = {0, 0, 32, 64};
    tmx_map* map = GetMap(0);
    int currentMap = 0;
    UpdatePlayerPosition(map, &Player);
    StartEnemies();
    
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
        
        //mainMenu();
/*         mapCanvas(currentMap, map);
        if(IsKeyPressed(KEY_P))
        {
            printf("Currentmap agora é o map%d\n", currentMap+1);
        }
        DrawRectangleRec(Player, RED);
        
        if(CheckObjgr(map, &Player, "Portas"))
        {
            DrawText("Press E to enter", Player.x-10, Player.y-10, 20, WHITE);
            if (IsKeyPressed(KEY_E))
            {
                UpdateMap(map, &Player, &currentMap);
                map = GetMap(currentMap);
                printf("Currentmap agora é o map%d\n", currentMap+1);
            }
        } */
        //FoundEnemyCanvas();
        //battleMenu();
        UpdateGameActions();
    

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
