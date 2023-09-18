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
                        
                    
               DrawRectangle(50, 400, 1200, 80, VIOLET);
               DrawText("TUTORIAL:",80, 400, 30, WHITE); //
               DrawText("Você deve ganhar a maioria dos confrontos. Para isso, leve o diagrama abaixo como base.",100, 445, 25, WHITE);
            
                DrawRectangle(50, 950, 700, 70, VIOLET);
                DrawText("Pressione ENTER para continuar",80, 970, 30, WHITE); 
           
            
         
            EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();                  // Fecha a janela e o contexto OpenGL
    return 0;
}