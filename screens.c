#include "resourcesIdx.h"
#include "screens.h"
#include "stdlib.h"
#include "raylib.h"
#include "load.h"
#include "sprites.h"
#include <tmx.h>

void (*activeScreen)() = NULL;
const int screenWidth = 1280;
const int screenHeight = 1024;

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
        //INICIAR JOGO
    }
    if(IsKeyPressed(KEY_ENTER)&&(selecao==1)){
        //CREDITOS
    }
    if(IsKeyPressed(KEY_ENTER)&&(selecao==2)){
        //EXIT
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

void mapCanvas(){
    static int started = 0;
    
    tmx_map *map = GetMap(Map_fase1);

	if (!map) {
		tmx_perror("Cannot load map");
        return;
	}

    render_map(map);
}