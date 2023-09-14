#include "include/items.h"
#include "include/combat.h"
#include "include/enemy.h"
#include "include/arena.h"
#include "include/game.h"
#include "raylib.h"
int main(void)
{
    // Inicialização
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - sprite anim");

    
    Texture2D Frente = LoadTexture("include/Personagens/!Persoangem/Frente.png");
    Texture2D Tras = LoadTexture("include/Personagens/!Persoangem/Costas.png");
    Texture2D Esquerda = LoadTexture("include/Personagens/!Persoangem/Esquerda.png");
    Texture2D Direita = LoadTexture("include/Personagens/!Persoangem/Direita.png");
    Texture2D Comeco = LoadTexture("include/Personagens/!Persoangem/Comeco.png");    // Texture loading

    Vector2 position = { 350.0f, 280.0f };
    Rectangle frameRec = { 0.0f, 0.0f, (float)Frente.width/4, (float)Direita.height };
    int currentFrame = 0;
    int flag=0;
    int framesSpeed = 10;            
    int framesCounter=0;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        framesCounter++;

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 3) currentFrame = 0;

            frameRec.x = (float)currentFrame*(float)Frente.width/4;
        }

        // Movimento do personagem
        if (IsKeyDown(KEY_UP)){ position.y -= 2.0f;flag=0;}
        if (IsKeyDown(KEY_DOWN)) {position.y += 2.0f;flag=1;}
        if (IsKeyDown(KEY_RIGHT)){position.x += 2.0f;flag=2;}
        if (IsKeyDown(KEY_LEFT)){ position.x -= 2.0f;flag=3;}
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            //desenhar posição do personagem de acordo com a movimentação do personagem
            if(flag==0)DrawTextureRec(Frente, frameRec, position, WHITE);
            if(flag==1)DrawTextureRec(Tras, frameRec, position, WHITE);
            if(flag==2)DrawTextureRec(Direita, frameRec, position, WHITE);
            if(flag==3)DrawTextureRec(Esquerda, frameRec, position, WHITE);
            if(flag == 4)DrawTextureV(Comeco, position, WHITE); 

        EndDrawing();
        flag=4;
        
    }

    // Fechandp o jogo
    //--------------------------------------------------------------------------------------
    UnloadTexture(Frente);       
    UnloadTexture(Tras);
    UnloadTexture(Direita);
    UnloadTexture(Esquerda);
    UnloadTexture(Comeco);
    CloseWindow();                
    //--------------------------------------------------------------------------------------

    return 0;
}

