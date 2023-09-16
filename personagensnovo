#include "raylib.h"
#define VIOLET     (Color){ 135, 60, 190, 255 }
#define DARKBLUE   (Color){ 0, 82, 172, 255 }
#define SKYBLUE    (Color){ 102, 191, 255, 255 }
#define BLUE       (Color){ 0, 121, 241, 255 }

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 1024;
    int selecao = 0;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - gif playing");

    Texture2D background = LoadTexture(""); 
    Vector2 img = {0,0};
    SetTargetFPS(60);
    
    ToggleFullscreen();
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
                    cor = BLUE; // Muda a cor do retangulo selecionado
                }
                DrawRectangle(130 * i + 50, 750, 100, 100, cor);
            }
            DrawRectangleLines(40, 710, 1180, 200, BLUE);
            DrawRectangle(400, 50, 480, 100, DARKBLUE); // pontos
            DrawRectangle(950,200, 240, 240, DARKBLUE);
            DrawRectangle(770,250, 150, 150, DARKBLUE);
            DrawRectangle(265,450, 150, 150, DARKBLUE); // oq vai aparecer o personagem 
            DrawRectangle(40, 370, 200, 270, DARKBLUE); // maior do canto
            
            EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();                  // Fecha a janela e o contexto OpenGL
    return 0;
}