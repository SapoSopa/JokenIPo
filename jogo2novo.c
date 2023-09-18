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

int main(){
    const int screenWidth = 1280;
    const int screenHeight = 720;
    float tamanho = 0;
      
    int selecao = 0;//(0 é Play) (1 é creditos) (2 é exit)

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - gif playing");
    
    Texture2D background = LoadTexture("C:\\Users\\Millena e Maya\\Documents\\Linguagem C\\torre.png"); 
    Vector2 img = {0,0};//VALOR ONDE A IMAGEM DO FUNDO VAI INICIAR
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    int subir = 1;
    tamanho = (float) screenWidth/ (float)background.width; 
    
    // ToggleFullscreen();
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if ((img.y <= -400)&& (subir == 1)){
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
                DrawPropRectangle(0.3 * i + 0.25, 0.73, 250, 100, cor);
            }
            DrawPropRectangle(0.03, 0.39, 450, 100, VIOLET);
            DrawPropCenteredText("RUN",0.34, 0.8, 40, WHITE);
            DrawPropCenteredText("FIGHT",0.65, 0.8, 40, WHITE);
            DrawPropCenteredText("or",0.5, 0.8, 35, BLACK);
            DrawPropRectangle(0.77, 0.13, 230, 260, VIOLET);
            DrawRectangleLines(GetScreenWidth() * 0.03, GetScreenHeight() * 0.53, 1180, 300, VIOLET);
            
            
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
            DrawPropCircle(0.3, 0.5, 105, MAGENTA);
            DrawPropCircle(0.5, 0.5, 105, BLUE);
            DrawPropCircle(0.7, 0.5, 105, BLUE);
            DrawPropCircle(0.3, 0.5, 100, VIOLET);
            DrawPropCircle(0.5, 0.5, 100, DARKBLUE); 
            DrawPropCircle(0.7, 0.5, 100, DARKBLUE);
            DrawPropCenteredText("PLAY",0.3, 0.5, 40, WHITE);
            DrawPropCenteredText("CREDITS",0.5, 0.5, 40, SKYBLUE);
            DrawPropCenteredText("EXIT",0.7, 0.5, 40, SKYBLUE);
            }
            if(selecao==1){
            DrawPropCircle(0.3, 0.5, 105, BLUE);
            DrawPropCircle(0.5, 0.5, 105, MAGENTA);
            DrawPropCircle(0.7, 0.5, 105, BLUE);
            DrawPropCircle(0.3, 0.5, 100, DARKBLUE);
            DrawPropCircle(0.5, 0.5, 100, VIOLET); 
            DrawPropCircle(0.7, 0.5, 100, DARKBLUE);
            DrawPropCenteredText("PLAY",0.3, 0.5, 40, SKYBLUE);
            DrawPropCenteredText("CREDITS",0.5, 0.5, 40, WHITE);
            DrawPropCenteredText("EXIT",0.7, 0.5, 40, SKYBLUE);
            }
            if(selecao==2){
            DrawPropCircle(0.3, 0.5, 105, BLUE);
            DrawPropCircle(0.5, 0.5, 105, BLUE);
            DrawPropCircle(0.7, 0.5, 105, MAGENTA);
            DrawPropCircle(0.3, 0.5, 100, DARKBLUE);
            DrawPropCircle(0.5, 0.5, 100, DARKBLUE); 
            DrawPropCircle(0.7, 0.5, 100, VIOLET);
            DrawPropCenteredText("PLAY",0.3, 0.5, 40, SKYBLUE);
            DrawPropCenteredText("CREDITS",0.5, 0.5, 40, SKYBLUE);
            DrawPropCenteredText("EXIT",0.7, 0.5, 40, WHITE);
            }
        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();                  
 
    return 0;
}
