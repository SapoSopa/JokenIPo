#include <raylib.h>
#include <math.h>


typedef struct{
    Vector2 position;
    float radius;
}personagem;
int main(void)
{
    // Inicialização
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - sprite anim");

    
    Texture2D Frente = LoadTexture("!Persoangem/Costas.png");
    Texture2D Tras = LoadTexture("!Persoangem/Frente.png");
    Texture2D Esquerda = LoadTexture("!Persoangem/Esquerda.png");
    Texture2D Direita = LoadTexture("!Persoangem/Direita.png");
    Texture2D Comeco = LoadTexture("!Persoangem/Comeco.png");    // Texture loading

    
    Rectangle frameRec = { 0.0f, 0.0f, (float)Esquerda.width/4, (float)Direita.height };
    int currentFrame = 0;
    int flag=0;
    int framesSpeed = 10;            
    int framesCounter=0;
    personagem.position = {350.0f, 280.0f};
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Rectangle ParedeLatD= {};
    Rectangle ParedeLatE= {};
    Rectangle ParedeBaixo= {};
    
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
        if (IsKeyDown(KEY_UP)){ personagem.position.y -= 2.0f;flag=0;}
        
        if (IsKeyDown(KEY_DOWN)) {
            personagem.position.y += 2.0f;
            flag=1;
            if(CheckCollisionCircleRec(personagem.position, radius, ParedeBaixo )){
                personagem.position.y = ParedeBaixo.position.y + personagem.radius;
            }
        }
        if (IsKeyDown(KEY_RIGHT)){
            personagem.position.x += 2.0f;
            flag=2;
            
            if(CheckCollisionCircleRec(personagem.position, radius, ParedeLatD )){
                personagem.position.x = ParedeLatD.Position.x - personagem.radius;
            }
        }
        
        if (IsKeyDown(KEY_LEFT)){ 
            personagem.position.x -= 2.0f;
            flag=3;
            if(CheckCollisionCircleRec(personagem.position, radius, ParedeLatE )){
                personagem.position.x = ParedeLatD.Position.x + personagem.radius;
            }
        }
        
        //if(CheckCollisionCircleRec(personagem.position, radius, ))
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            //desenhar posição do personagem de acordo com a movimentação do personagem
            if(flag==0)DrawTextureRec(Frente, frameRec, personagem.position, WHITE);
            if(flag==1)DrawTextureRec(Tras, frameRec, personagem.position, WHITE);
            if(flag==2)DrawTextureRec(Direita, frameRec, personagem.position, WHITE);
            if(flag==3)DrawTextureRec(Esquerda, frameRec, personagem.position, WHITE);
            if(flag == 4)DrawTextureV(Comeco, personagem.position, WHITE); 

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
