#include "raylib.h"

#define VIOLET     (Color){ 135, 60, 190, 255 }
#define DARKBLUE   (Color){ 0, 82, 172, 255 }
#define SKYBLUE    (Color){ 102, 191, 255, 255 }
#define BLUE       (Color){ 0, 121, 241, 255 }
#define WHITE      (Color){ 255, 255, 255, 255 }

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

   int main() {
   
    const int screenWidth = 1280;
    const int screenHeight = 1024;
    int selecao = 0;
    

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - gif playing");

    Texture2D background = LoadTexture(""); 
    Vector2 img = {0,0};
    SetTargetFPS(60);
    

    while (!WindowShouldClose())
    {
       

        BeginDrawing();
        
                // Carrega uma textura de um arquivo de imagem
                Texture2D texture0 = LoadTexture("C:\\Users\\User\\Desktop\\JOGO\\pedra.png");
                Texture2D texture1 = LoadTexture("C:\\Users\\User\\Desktop\\JOGO\\arma.png");
                Texture2D texture2 = LoadTexture("C:\\Users\\User\\Desktop\\JOGO\\agua.png");
                Texture2D texture3 = LoadTexture("C:\\Users\\User\\Desktop\\JOGO\\ar.png");
                Texture2D texture4 = LoadTexture("C:\\Users\\User\\Desktop\\JOGO\\papel.png");
                Texture2D texture5 = LoadTexture("C:\\Users\\User\\Desktop\\JOGO\\esponja.png");
                Texture2D texture6 = LoadTexture("C:\\Users\\User\\Desktop\\JOGO\\humano.png");
                Texture2D texture7 = LoadTexture("C:\\Users\\User\\Desktop\\JOGO\\tesoura.png");
                Texture2D texture8 = LoadTexture("C:\\Users\\User\\Desktop\\JOGO\\fogo.png");
                
            
                //circulos
                Vector2 centerPoint= {GetScreenWidth()*0.5,GetScreenHeight()*0.7};
                float radius= GetScreenHeight()/6;
              
               for(int i=0;i<9;i++){
                    
                   DrawCircle(centerPoint.x +radius *cos(i*2*PI/9),centerPoint.y+radius*sin(i*2*PI/9),46,WHITE);
                  
                }
                        // Desenha a textura na tela
                        DrawTexture(texture0, 651, 525,WHITE);
                        DrawTexture(texture1, 755, 591,WHITE);
                        DrawTexture(texture2, 792, 700,WHITE);
                        DrawTexture(texture3, 762, 811,WHITE);
                        DrawTexture(texture4, 649, 869,WHITE);
                        DrawTexture(texture5, 530, 844,WHITE);
                        DrawTexture(texture6, 462,754,WHITE);
                        DrawTexture(texture7, 468,634,WHITE);
                        DrawTexture(texture8, 542,544,WHITE);
                        
                    
               DrawPropRectangle(0.05, 0.40, 1200, 80, VIOLET);
               DrawPropCenteredText("TUTORIAL:",0.12, 0.42, 30, WHITE); 
               DrawPropCenteredText("Você deve ganhar a maioria dos confrontos. Para isso, leve o diagrama abaixo como base.",0.51, 0.45, 25, WHITE);
            
                
              
               DrawPropRectangle(0.04, 0.92, 700, 70, VIOLET);
               DrawPropCenteredText("Pressione ENTER para continuar",0.25, 0.95, 30, WHITE); 
           
            
         
            EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();                  // Fecha a janela e o contexto OpenGL
    return 0;
}