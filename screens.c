#include "resourcesIdx.h"
#include "screens.h"
#include "stdlib.h"
#include "raylib.h"
#include "load.h"
#include "sprites.h"
#include "canvas.h"
#include <tmx.h>

#include "math.h"

const int screenWidth = 1280;
const int screenHeight = 1024;

void SetActiveScreen(void (*screen)()){
    activeScreen = screen;
}

void UpdateScreen(){
    if (activeScreen != NULL)
        (*activeScreen)();
}

void mainMenu(){
    static int selecao = 0;//(0 é Play) (1 é creditos) (2 é exit)
    Texture2D* background = GetTexture(Texture_torre); 
    static Vector2 img = {0,0};//VALOR ONDE A IMAGEM DO FUNDO VAI INICIAR
    static int subir = 1;
    float tamanho = (float) screenWidth / (float)background->width; 

    if ((img.y <= -(background->height)/2)&& (subir == 1)){
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
        //PLAY
        SetActiveScreen(&FoundEnemyCanvas); //temporário
    }
    if(IsKeyPressed(KEY_ENTER)&&(selecao==1)){
        //CREDITOS
    }
    if(IsKeyPressed(KEY_ENTER)&&(selecao==2)){
        //EXIT
        QuitApplication();
    }

    //COLOCANDO A IMAGEM DE BACKGROUND ANTES DE DESENHAR TODOS OS CIRCULOS
    DrawTextureEx((*background), img,0 , tamanho, GRAY);
    

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
}

void FoundEnemyCanvas(){
    static int selecao = 0;
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
}

void battleMenu(){
    static int selecao = 0;
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

    // Draw
    Texture2D* background = GetTexture(Texture_torre); 
    Vector2 img = {0,0};

    DrawTextureV(*background,img , GRAY);
    DrawTexturePro(*background, (Rectangle){ 0.0f, 0.0f, (float)background->width, (float)background->height }, 
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

void mapCanvas(){
    static int started = 0;
    
    tmx_map *map = GetMap(Map_fase11);

	if (!map) {
		tmx_perror("Cannot load map");
        return;
	}
	
    render_map(map);
}
