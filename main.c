#include "raylib.h"
#include <tmx.h>
#include "include/items.h"
#include "include/game.h"
#include "include/enemy.h"
#include "include/combat.h"
#include "include/load.h"
#include "include/screens.h"
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


static int isRunning = 0;

void SetRunning(int value)
{
    isRunning = value;
}

//tava perdido por ai e veio pra cá... essa bagunça que to fazendo pelo menos funciona, mas organização 0
typedef struct {
    char *name;
    bool defeated;
} EnemyList;

bool EnemyDefeated(tmx_map *map, Rectangle *playerRect, EnemyList *enemies);

tmx_map** GetCurrentMap();

int EnemyId(tmx_map *map, Rectangle *playerRect, EnemyList *enemies);

State GameState = Menu;

void mainWindow(){
	int monitor = GetCurrentMonitor();

    InitAudioDevice();
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
void UpdateMovement();

static  EnemyList enemies[16] = {{"Inimigo I", false},
                        {"Inimigo II", false},
                        {"Inimigo III", false},
                        {"Inimigo IV", false},
                        {"Inimigo V", false},
                        {"Inimigo VI", false},
                        {"Inimigo VII", false},
                        {"Inimigo VIII", false},
                        {"Inimigo IX", false},
                        {"Inimigo X", false},
                        {"Inimigo XI", false},
                        {"Inimigo XII", false},
                        {"Inimigo XIII", false},
                        {"Inimigo XIV", false},
                        {"Inimigo XV", false},
                        {"BOSS", false}};

int main () {
    mainWindow();
    SetActiveScreen(&mainMenu);
    
    // load somethings, temporaly here
    M_LoadMap();
    M_LoadTexture();

    // Player setup
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
        
        if(isRunning)
        {
            mapCanvas(currentMap, map);
            DrawRectangle(Player.x, Player.y, Player.width, Player.height, RED);
            if(IsKeyDown(KEY_G))
            {
                if(IsKeyPressed(KEY_RIGHT))
                {
                    currentMap++;
                    map = GetMap(currentMap);
                    UpdatePlayerPosition(map, &Player);
                }
                if(IsKeyPressed(KEY_LEFT))
                {
                    currentMap--;
                    map = GetMap(currentMap);
                    UpdatePlayerPosition(map, &Player);
                }
            }
            if(CheckObjgr(map, &Player, "Inimigos"))
            {
                if(!EnemyDefeated(map, &Player, enemies))
                {
                    DrawText("Press E to interact", Player.x-10, Player.y-10, 20, WHITE);
                    if (IsKeyPressed(KEY_E))
                    {
                        SetActiveScreen(&FoundEnemyCanvas);
                        isRunning = 0;
                    }
                }
                else if(CheckObjgr(map, &Player, "Portas"))
                {
                    DrawText("Press E to enter", Player.x-10, Player.y-10, 20, WHITE);
                    if (IsKeyPressed(KEY_E))
                    {
                        UpdateMap(map, &Player, &currentMap);
                        map = GetMap(currentMap);
                        }
                    }
                
                } 
                
            
            //FoundEnemyCanvas();

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

tmx_map** GetCurrentMap() 
{
    static tmx_map* map = NULL;
    return &map;
}

int EnemyId(tmx_map *map, Rectangle *playerRect, EnemyList *enemies)
{
    if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo I"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo I") == 0)
            {
                return 0;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo II"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo II") == 0)
            {
                return 1;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo III"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo III") == 0)
            {
                return 2;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo IV"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo IV") == 0)
            {
                return 3;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo V"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo V") == 0)
            {
                return 4;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo VI"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo VI") == 0)
            {
                return 5;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo VII"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo VII") == 0)
            {
                return 6;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo VIII"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo VIII") == 0)
            {
                return 7;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo IX"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo IX") == 0)
            {
                return 8;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo X"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo X") == 0)
            {
                return 9;
            }
        }
    }else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo XI"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo XI") == 0)
            {
                return 10;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo XII"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo XII") == 0)
            {
                return 11;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo XIII"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo XIII") == 0)
            {
                return 12;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo XIV"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo XIV") == 0)
            {
                return 13;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo XV"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo XV") == 0)
            {
                return 14;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "BOSS"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "BOSS") == 0)
            {
                return 15;
            }
        }
    }
}

bool EnemyDefeated(tmx_map *map, Rectangle *playerRect, EnemyList *enemies)
{
    if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo I"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo I") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo II"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo II") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo III"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo III") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo IV"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo IV") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo V"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo V") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo VI"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo VI") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo VII"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo VII") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo VIII"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo VIII") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo IX"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo IX") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo X"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo X") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo XI"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo XI") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo XII"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo XII") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo XIII"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo XIII") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo XIV"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo XIV") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "Inimigo XV"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "Inimigo XV") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
    else if (CheckObjName(map, &playerRect, "Inimigos", "BOSS"))
    {
        for (int i = 0; i < 16; i++)
        {
            if (strcmp(enemies[i].name, "BOSS") == 0)
            {
                return enemies[i].defeated;
            }
        }
    }
}
