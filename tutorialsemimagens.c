#include "raylib.h"
#define VIOLET     (Color){ 135, 60, 190, 255 }
#define DARKBLUE   (Color){ 0, 82, 172, 255 }
#define SKYBLUE    (Color){ 102, 191, 255, 255 }
#define BLUE       (Color){ 0, 121, 241, 255 }
#define WHITE      (Color){ 255, 255, 255, 255 }

   int main() {
   
    const int screenWidth = 1280;
    const int screenHeight = 1024;
    int selecao = 0;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - gif playing");

    Texture2D background = LoadTexture(""); 
    Vector2 img = {0,0};
    SetTargetFPS(60);
    
    //ToggleFullscreen();
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        if(IsKeyPressed(KEY_LEFT)&&(selecao>0)){
            selecao--;
        }
        if(IsKeyPressed(KEY_RIGHT)&&(selecao<8)){
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
                case 3:
                    //item 3
                    break;
                case 4:
                    //item 4
                    break;
                case 5:
                    //item 5
                    break;
                case 6:
                    //item 6
                    break;
                case 7: 
                    //item 7
                    break;
                case 8:
                    //item 6
                    break;
                case 9: 
                    //item 7
                    break;       
            }
        }

        BeginDrawing();
            DrawTextureV(background,img , GRAY);
            DrawTexturePro(background, (Rectangle){ 0.0f, 0.0f, (float)background.width, (float)background.height }, 
            (Rectangle){ 0, 0, screenWidth, screenHeight }, (Vector2){ 0, 0 }, 0.0f, WHITE); 

            for(int i = 0; i < 9; i++){
                Color cor = DARKBLUE;
                if(i == selecao){
                    cor = VIOLET; // Muda a cor do círculo selecionado
                }
                
                //TEXTO
                
               DrawText("TUTORIAL:",80, 400, 30, VIOLET); //
               DrawText("Você deve ganhar a maioria dos confrontos, para isso leve o diagrama abaixo como base",100, 445, 25, MAGENTA);
            
              
               //Desehando nove circulinhos de cor branca
                
                /*
                        *1
                     9*     *2
                  8  *       *3
                    7 *     *4
                       6*  *5
                */
                DrawText("pedra",510, 470, 25, VIOLET);
                DrawCircle(540, 539, 45, WHITE);  // 1
                
                DrawText("arma",665, 515, 25, VIOLET);
                DrawCircle(678, 590, 45, WHITE); //2
                
                DrawText("água",732, 631, 25, VIOLET);
                DrawCircle(740, 700, 45, WHITE); //3
                
                DrawText("ar",742, 861, 25, VIOLET);
                DrawCircle(740, 810, 45, WHITE); //4
                
                DrawText("papel",628, 915, 25, VIOLET);
                DrawCircle(650, 870, 45, WHITE); //5
                
                DrawText("esponja",465, 939, 25, VIOLET);
                DrawCircle(509, 890, 45, WHITE); //6
                
                DrawText("humano",340, 859, 25, VIOLET);
                DrawCircle(401, 815, 45, WHITE); //7
                
                DrawText("tesoura",289, 639, 25, VIOLET);
                DrawCircle(395, 710, 45, WHITE); //8
                
                DrawText("fogo",391, 522, 25, VIOLET);
                DrawCircle(435, 600, 45, WHITE); //9
        
            
                DrawText("Pressione ENTER para continuar",80, 980, 30, VIOLET); 
              
                
            }
         
            EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();                  // Fecha a janela e o contexto OpenGL
    return 0;
}