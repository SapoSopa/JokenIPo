#include "raylib.h"
#define PINK       (Color){ 255, 109, 194, 255 }
#define MAGENTA    (Color){ 255, 0, 255, 255 }
#define VIOLET     (Color){ 135, 60, 190, 255 }
#define DARKBLUE   (Color){ 0, 82, 172, 255 }
#define SKYBLUE    (Color){ 102, 191, 255, 255 }
#define BLUE       (Color){ 0, 121, 241, 255 }

void DrawFixedPropRectangle(float xProp, float yProp, float wProp, float hProp, Color color){
    DrawRectangle(GetScreenWidth() * xProp, GetScreenHeight() * yProp, GetScreenWidth() * wProp, GetScreenHeight() * hProp, color);
}
void DrawFixedPropCircle(float xProp, float yProp, float rProp, Color color){
    DrawCircle(GetScreenWidth() * xProp, GetScreenHeight() * yProp, GetScreenWidth() * rProp, color);
}
void DrawFixedPropText(const char *text, float xProp, float yProp, float fontSizeProp, Color color){
    DrawText(text, GetScreenWidth() * xProp, GetScreenHeight() * yProp, (int) (GetScreenHeight() * fontSizeProp), color);
}


void DrawPropCenteredTexture(Texture2D texture, float xProp, float yProp, Color tint){
    DrawTexture(texture, GetScreenWidth() * xProp - texture.width / 2, GetScreenHeight() * yProp - texture.height / 2, tint);
}
void DrawPropCenteredText(const char *text, float xProp, float yProp, int fontSize, Color color){
    DrawText(text, GetScreenWidth() * xProp - MeasureText(text, fontSize) / 2.0, GetScreenHeight() * yProp - fontSize / 2.0, fontSize, color);
}
void DrawPropCenteredRectangle(float xProp, float yProp, float width, float height, Color color){
    DrawRectangle(GetScreenWidth() * xProp - width / 2, GetScreenHeight() * yProp - height / 2, width, height, color);
}


void DrawPropTexture(Texture2D texture, float xProp, float yProp, Color tint){
    DrawTexture(texture, GetScreenWidth() * xProp, GetScreenHeight() * yProp, tint);
}
void DrawCenteredText(const char *text, int posX, int posY, int fontSize, Color color){
    DrawText(text, posX - MeasureText(text, fontSize) / 2.0, posY - fontSize / 2.0, fontSize, color);
}
void DrawPropCircle(float xProp, float yProp, float radius, Color color){
    DrawCircle(GetScreenWidth() * xProp, GetScreenHeight() * yProp, radius, color);
}
void DrawPropRectangle(float xProp, float yProp, float width, float height, Color color){
    DrawRectangle(GetScreenWidth() * xProp, GetScreenHeight() * yProp, width, height, color);
}


void DrawPropText(const char *text, float xProp, float yProp, int fontSize, Color color){
    DrawText(text, GetScreenWidth() * xProp, GetScreenHeight() * yProp, fontSize, color);
}
void DrawCenteredTexture(Texture2D texture, int posX, int posY, Color tint){
    DrawTexture(texture, posX - texture.width / 2, posY - texture.height / 2, tint);
}
void DrawCenteredRectangle(int posX, int posY, int width, int height, Color color){
    DrawRectangle(posX - width / 2, posY - height / 2, width, height, color);
}
int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
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
                    //pers 1
                    break;
                case 2:
                    //pers 2
                    break;
                case 3:
                    //pers 3
                    break;
                case 4:
                    //pers 4
                    break;
                case 5:
                    //pers 5
                    break;
                case 6:
                    //pers 6
                    break;
                case 7: 
                    //pers 7
                    break;
                case 8:
                    //pers 8
                    break;
                case 9: 
                    //pers 9
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
                DrawPropRectangle(0.101 * i + 0.05, 0.72, 100, 100, cor);
            }
            DrawPropRectangle(0.3, 0.03, 480, 100, DARKBLUE); // pontos
            DrawPropRectangle(0.795,0.18, 200, 270, DARKBLUE);
            DrawPropRectangle(0.64,0.3, 150, 150, DARKBLUE);
            DrawPropRectangle(0.22, 0.3, 150, 150, DARKBLUE); // oq vai aparecer o personagem 
            DrawPropRectangle(0.03, 0.18, 200, 270, DARKBLUE); // maior do canto
            DrawRectangleLines(GetScreenWidth() * 0.03, GetScreenHeight() * 0.65, 1180, 200, BLUE);
            EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();                  // Fecha a janela e o contexto OpenGL
    return 0;
}
