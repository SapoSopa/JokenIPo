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

//tava perdido por ai e veio pra cá... essa bagunça que to fazendo pelo menos funciona, mas organização 0
typedef struct {
    char *name;
    bool defeated;
} EnemyList;

bool EnemyDefeated(tmx_map *map, Rectangle *playerRect, EnemyList *enemies);

int EnemyId(tmx_map *map, Rectangle *playerRect, EnemyList *enemies);

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

    // olha os inimigos aqui


    // Player setup
    Rectangle Player = {0, 0, 32, 64};
    tmx_map* map = GetMap(1);
    int currentMap = 1;
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
        
        BeginDrawing();
        ClearBackground(BLACK);

        UpdateScreen();
        
        //mainMenu();
     mapCanvas(currentMap, map);
        if(IsKeyPressed(KEY_P))
        {
            printf("Currentmap agora é o map%d\n", currentMap+1);
        }

        DrawRectangleRec(Player, RED);
        
        if(!CheckObjgr(map, &Player, "Inimigos"))
        {
            if(!EnemyDefeated(map, &Player, enemies))
            {
                DrawText("Press E to interact", Player.x-10, Player.y-10, 20, WHITE);
                if (IsKeyPressed(KEY_E))
                {
                    //chama pra conversar sobre lutar e quando ganhar trocar o valor de defeated pra true
                }
            }
        } 
        else if(CheckObjgr(map, &Player, "Portas"))
        {
            DrawText("Press E to enter", Player.x-10, Player.y-10, 20, WHITE);
            if (IsKeyPressed(KEY_E))
            {
                UpdateMap(map, &Player, &currentMap);
                printf("o mapa %d foi carregado\n", currentMap+1);
                map = GetMap(currentMap);
                }
            }
            
        
        //FoundEnemyCanvas();
        //battleMenu();
        //UpdateGameActions();
       // TutorialCanvas();


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
