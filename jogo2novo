#include "raylib.h"
#define PINK       (Color){ 255, 109, 194, 255 }
#define MAGENTA    (Color){ 255, 0, 255, 255 }
#define VIOLET     (Color){ 135, 60, 190, 255 }
#define DARKBLUE   (Color){ 0, 82, 172, 255 }
#define SKYBLUE    (Color){ 102, 191, 255, 255 }
#define BLUE       (Color){ 0, 121, 241, 255 }

int main(){
    const int screenWidth = 1280;
    const int screenHeight = 1024;
    float tamanho = 0;
      
    int selecao = 0;//(0 é Play) (1 é creditos) (2 é exit)

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - gif playing");
    
    Texture2D background = LoadTexture("D:\\Users\\mfmn\\Documents\\torre.png"); 
    Vector2 img = {0,0};//VALOR ONDE A IMAGEM DO FUNDO VAI INICIAR
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    int subir = 1;
    tamanho = (float) screenWidth/ (float)background.width; 
    
    ToggleFullscreen();
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if ((img.y <= -300)&& (subir == 1)){
            subir = 2;
        }
        if ((img.y >= 0) && (subir == 2)){
            subir = 1;
        }
        // Update
        
        if(subir == 1)
        img.y -= 1;
        if (subir ==2)
           img.y += 1;
        //A IMAGEM DO FUNDO DESCER
        if(IsKeyPressed(KEY_LEFT)&&(selecao>0)){
            selecao--;
        }
        if(IsKeyPressed(KEY_RIGHT)&&(selecao<2)){
            selecao++;
        }
        if(IsKeyPressed(KEY_ENTER)&&(selecao==0)){
            //INICIAR JOGO
               while (!WindowShouldClose())
    {
        // Update
        if(IsKeyPressed(KEY_LEFT)&&(selecao>0)){
            selecao--;
        }
        if(IsKeyPressed(KEY_RIGHT)&&(selecao<1)){
            selecao++;
        }
        if(IsKeyPressed(KEY_ENTER)){
            switch(selecao){
                case 1:
                    //item 1
                    break;
                case 2:
                    //item 2
                    break;     
            }
        }
        BeginDrawing();
            ClearBackground(WHITE);
            
            // Ajuste a posição e tamanho dos retângulos
            for(int i = 0; i < 2; i++){
                Color cor = VIOLET;
                if(i == selecao){
                    cor = DARKBLUE; // Muda a cor do retângulo selecionado
                }
                DrawRectangle(350 * i + 350, 760, 250, 100, cor);
            }
            //DrawRectangleLines(40, 620, 1180, 300, BLUE);
            DrawRectangle(40, 520, 450, 100, VIOLET);
            DrawText("Texto:",60, 680, 35, VIOLET); // isa vai escrever e posicionar
            DrawText("RUN",430, 795, 40, WHITE);
            DrawText("FIGHT",770, 795, 40, WHITE);
            DrawText("or",630, 784, 35, BLACK);
            DrawRectangleLines(40, 620, 1180, 300, VIOLET);
            DrawRectangle(950, 50, 250, 350, VIOLET);
            
            
            EndDrawing();
    }
        }
        if(IsKeyPressed(KEY_ENTER)&&(selecao==1)){
            //CREDITOS
        }
        if(IsKeyPressed(KEY_ENTER)&&(selecao==2)){
            //EXIT
        }
 
        BeginDrawing();
           DrawTextureEx(background, img,0 , tamanho, GRAY);//COLOCANDO A IMAGEM DE BACKGROUND ANTES DE DESENHAR TODOS OS CIRCULOS
         
            
            if(selecao==0){
            DrawCircle(400, 500, 105, MAGENTA);
            DrawCircle(650, 500, 105, BLUE);
            DrawCircle(900, 500, 105, BLUE);
            DrawCircle(400, 500, 100, VIOLET);
            DrawCircle(650, 500, 100, DARKBLUE); 
            DrawCircle(900, 500, 100, DARKBLUE);
            DrawText("PLAY",345, 490, 40, WHITE);
            DrawText("CREDITS",557, 490, 40, SKYBLUE);
            DrawText("EXIT",850, 490, 40, SKYBLUE);
            }
            if(selecao==1){
            DrawCircle(400, 500, 105, BLUE);
            DrawCircle(650, 500, 105, MAGENTA);
            DrawCircle(900, 500, 105, BLUE);
            DrawCircle(400, 500, 100, DARKBLUE);
            DrawCircle(650, 500, 100, VIOLET); 
            DrawCircle(900, 500, 100, DARKBLUE);
            DrawText("PLAY",345, 490, 40, SKYBLUE);
            DrawText("CREDITS",557, 490, 40, WHITE);
            DrawText("EXIT",850, 490, 40, SKYBLUE);
            }
            if(selecao==2){
            DrawCircle(400, 500, 105, BLUE);
            DrawCircle(650, 500, 105, BLUE);
            DrawCircle(900, 500, 105, MAGENTA);
            DrawCircle(400, 500, 100, DARKBLUE);
            DrawCircle(650, 500, 100, DARKBLUE); 
            DrawCircle(900, 500, 100, VIOLET);
            DrawText("PLAY",345, 490, 40, SKYBLUE);
            DrawText("CREDITS",557, 490, 40, SKYBLUE);
            DrawText("EXIT",850, 490, 40, WHITE);
            }
        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();                  
 
    return 0;
}