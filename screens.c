#include "resourcesIdx.h"
#include "screens.h"
#include "stdlib.h"
#include "raylib.h"
#include "load.h"
#include "sprites.h"
#include <tmx.h>

const int screenWidth = 1280;
const int screenHeight = 1024;

void SetActiveScreen(void (*screen)()){
    activeScreen = screen;
}

void UpdateScreen(){
    if (activeScreen != NULL)
        (*activeScreen)();
    //printf("No active screen\n");
}

void mainMenu(){
    static int selecao = 0;//(0 é Play) (1 é creditos) (2 é exit)
    Texture2D* background = GetTexture(Texture_torre); 
    static Vector2 img = {0,0};//VALOR ONDE A IMAGEM DO FUNDO VAI INICIAR
    static int subir = 1;
    float tamanho = (float) screenWidth/ (float)background->width; 

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
}

void FoundEnemyCanvas(){
    static int selecao = 0;
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

    // Draw
    // Ajuste a posição e tamanho dos retângulos
    for(int i = 0; i < 2; i++){
        Color cor = VIOLET;
        if(i == selecao){
            cor = DARKBLUE; // Muda a cor do retângulo selecionado
        }
        DrawRectangle(350 * i + 350, 860, 250, 100, cor);
    }
    DrawRectangle(40, 620, 450, 100, VIOLET);
    DrawText("Texto:",60, 780, 35, VIOLET); // isa vai escrever e posicionar
    DrawText("RUN",430, 895, 40, WHITE);
    DrawText("FIGHT",770, 895, 40, WHITE);
    DrawText("or",630, 889, 35, BLACK);
    DrawRectangleLines(40, 720, 1180, 300, VIOLET);
    DrawRectangle(950, 400, 230, 260, VIOLET);
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
        DrawRectangle(130 * i + 50, 550, 100, 100, cor);
    }
    DrawRectangleLines(40, 510, 1180, 200, BLUE);
    DrawRectangle(400, 50, 480, 100, DARKBLUE); // pontos
    DrawRectangle(1000,170, 200, 270, DARKBLUE);
    DrawRectangle(830,250, 150, 150, DARKBLUE);
    DrawRectangle(265, 250, 150, 150, DARKBLUE); // oq vai aparecer o personagem 
    DrawRectangle(40, 170, 200, 270, DARKBLUE); // maior do canto
}

void mapCanvas(){
    static int started = 0;
    
    tmx_map *map = GetMap(Map_fase4);

	if (!map) {
		tmx_perror("Cannot load map");
        return;
	}
	
    render_map(map);
}
