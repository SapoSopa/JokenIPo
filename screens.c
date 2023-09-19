#include "resourcesIdx.h"
#include "game.h"
#include "screens.h"
#include "stdlib.h"
#include "raylib.h"
#include "load.h"
#include "sprites.h"
#include "canvas.h"
#include <tmx.h>
#include "stdio.h"
#include "string.h"

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
    float tamanho = (float) GetScreenWidth() / (float)background->width; 

    //ajeitar a imagem de fundo ----------------------
    if ((img.y <= -(background->height)/2) && (subir == 1)){
        subir = 2;
    }
    if ((img.y >= 0) && (subir == 2)){
        subir = 1;
    }

    // Update
    if (subir == 1)
        img.y -= 1;
    if (subir == 2)
        img.y += 1;
    //A IMAGEM DO FUNDO DESCER
    if(IsKeyPressed(KEY_LEFT)&&(selecao>0)){
        selecao--;
    }
    if(IsKeyPressed(KEY_RIGHT)&&(selecao<2)){
        selecao++;
    }

    if(IsKeyPressed(KEY_ENTER)&&(selecao==0)){
        StartTutorial();
        //SetActiveScreen(&FoundEnemyCanvas); //temporário
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

void TutorialCanvas(){
    Vector2 centerPoint= {GetScreenWidth()*0.5,GetScreenHeight()*0.5};
    float radius= GetScreenHeight()/5;

    static int opcoes[9] = {Texture_rock, Texture_fire, Texture_scissors, Texture_human, Texture_sponge,
                            Texture_paper, Texture_air, Texture_water, Texture_gun};
    
    for(int i=0;i<9;i++){
        DrawCircle(centerPoint.x + radius *cos(i*2*PI/9), centerPoint.y + radius*sin(i*2*PI/9), 46, WHITE);
        DrawResCenteredTexture(*GetTexture(opcoes[i]), (Vector2){centerPoint.x +radius *cos(i*2*PI/9), centerPoint.y+radius*sin(i*2*PI/9)}, 0, 1.5, WHITE);
    }
    
    DrawFixedPropRectangle(0.02, 0.02, 0.96, 0.2, VIOLET);
    DrawPropText("TUTORIAL:",0.03, 0.03, 30, WHITE); 
    DrawPropText("Você deve ganhar a maioria dos confrontos. Para isso, leve o diagrama abaixo como base.", 0.06, 0.1, 25, WHITE);

    DrawFixedPropRectangle(0.02, 0.85, 0.6, 0.13, VIOLET);
    DrawPropText("Pressione ENTER para continuar", 0.03, 0.9, 30, WHITE);

    if (IsKeyPressed(KEY_ENTER)) {
        StartPlaying();
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
                StartBattle();
                break;
            case 2:
                StartPlaying();
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

    if(IsKeyPressed(KEY_LEFT)&&(selecao==0)){
        selecao = 8;
    }
    else if(IsKeyPressed(KEY_LEFT)&&(selecao>0)){
        selecao--;
    }
    if(IsKeyPressed(KEY_RIGHT)&&(selecao<8)){
        selecao++;
    }
    else if(IsKeyPressed(KEY_RIGHT)&&(selecao==8)){
        selecao = 0;
    }

    if(IsKeyPressed(KEY_ENTER)){
        DoPlayerChoice(selecao);
    }

    // Draw
    Texture2D* background = GetTexture(Texture_torre); 
    Vector2 img = {0,0};

    DrawTextureV(*background,img , GRAY);
    DrawTexturePro(*background, (Rectangle){ 0.0f, 0.0f, (float)background->width, (float)background->height }, 
    (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE); 

    for(int i = 0; i < 9; i++){
        Color cor = DARKBLUE;
        if(i == selecao){
            cor = BLUE; // Muda a cor do retangulo selecionado
        }
        DrawPropCenteredRectangle(0.1 * i + 0.1, 0.8, 100, 100, cor);
        DrawPropResCenteredTexture(*GetTexture(Texture_rock + i), (Vector2){0.1 * i + 0.1, 0.8}, 0, 1.5, WHITE);
        //DrawPropCenteredTexture(*GetTexture(Texture_rock + i), 0.1 * i + 0.1, 0.8, WHITE);
    }
    DrawPropRectangle(0.3, 0.03, 480, 100, DARKBLUE); // pontos
    DrawPropRectangle(0.795, 0.18, 200, 270, DARKBLUE);
    DrawPropRectangle(0.64, 0.3, 150, 150, DARKBLUE);
    DrawPropRectangle(0.22, 0.3, 150, 150, DARKBLUE); // oq vai aparecer o personagem 
    DrawPropRectangle(0.03, 0.18, 200, 270, DARKBLUE); // maior do canto
    DrawRectangleLines(GetScreenWidth() * 0.03, GetScreenHeight() * 0.65, GetScreenWidth() * 0.94, GetScreenHeight() * 0.3, BLUE);    
}

bool CheckObjName(tmx_map *map, Rectangle *playerRect, char *name, char *objName)
{
    tmx_layer *layer = NULL;
    layer = map->ly_head;
    while(layer)
    {
        if (layer->visible)
        {
            if (layer->type == L_OBJGR && layer->name && strcmp(layer->name, name) == 0)
            {
                if(layer->content.objgr)
                {
                    tmx_object *obj = layer->content.objgr->head;
                    while (obj)
                    {
                        if (obj->name && strcmp(obj->name, objName) == 0)
                        {
                            if (CheckCollisionRecs(*playerRect, (Rectangle){obj->x, obj->y, obj->width, obj->height}))
                            {
                                return true;
                            }
                        }
                        obj = obj->next;
                    }
                }
            }               
        }
        layer = layer->next;
    }
    return false;
}


bool CheckObjgr(tmx_map *map, Rectangle *playerRect, char *name)
{
    tmx_layer *layer = NULL;
    layer = map->ly_head;
    while(layer)
    {
        if (layer->visible)
        {
            if (layer->type == L_OBJGR && layer->name && strcmp(layer->name, name) == 0)
            {
                if(layer->content.objgr)
                {
                    tmx_object *obj = layer->content.objgr->head;
                    while (obj)
                    {
                        if (CheckCollisionRecs(*playerRect, (Rectangle){obj->x, obj->y, obj->width, obj->height}))
                        {
                            return true;
                        }
                        obj = obj->next;
                    }
                }
            }               
        }
        layer = layer->next;
    }
    return false;
}

void UpdatePlayerPosition(tmx_map *map, Rectangle *playerRect)
{
    tmx_layer *layer = NULL;
    layer = map->ly_head;
    bool achou = false;
    while(layer && !achou)
    {
        if (layer->visible)
        {
            if (layer->type == L_OBJGR && layer->name && strcmp(layer->name, "Pontos") == 0)
            {
                if(layer->content.objgr)
                {
                    tmx_object *obj = layer->content.objgr->head;
                    while (obj && !achou)
                    {
                        if (obj->name && strcmp(obj->name, "Player") == 0)
                        {
                            playerRect->x = obj->x;
                            playerRect->y = obj->y;
                            achou = true;
                        }
                        obj = obj->next;
                    }
                }
            }               
        }
        layer = layer->next;
    }
}

int CheckWhereToGo (tmx_map *map, Rectangle *playerRect)
{
    if(CheckObjName(map, playerRect, "Portas", "Porta_I"))
    {
        return Porta_I;
    }
    else if(CheckObjName(map, playerRect, "Portas", "Porta_II"))
    {
        return Porta_II;
    }
    else if(CheckObjName(map, playerRect, "Portas", "Porta_III"))
    {
        return Porta_III;
    }
    else if(CheckObjName(map, playerRect, "Portas", "Porta_IV"))
    {
        return Porta_IV;
    }
    else if(CheckObjName(map, playerRect, "Portas", "Porta_V"))
    {
        return Porta_V;
    }
    else if(CheckObjName(map, playerRect, "Portas", "Porta_VI"))
    {
        return Porta_VI;
    }
    else if(CheckObjName(map, playerRect, "Portas", "Porta_VII"))
    {
        return Porta_VII;
    }
    else if(CheckObjName(map, playerRect, "Portas", "Porta_VIII"))
    {
        return Porta_VIII;
    }
    else if(CheckObjName(map, playerRect, "Portas", "Porta_IX"))
    {
        return Porta_IX;
    }
    else if(CheckObjName(map, playerRect, "Portas", "Porta_X"))
    {
        return Porta_X;
    }
    else if(CheckObjName(map, playerRect, "Portas", "Porta_XI"))
    {
        return Porta_XI;
    }
    else
    {
        return -1;
    }
}

void UpdateMap(tmx_map *map, Rectangle *playerRect, int *currentMap)
{
    *currentMap = CheckWhereToGo(map, playerRect);
    UpdatePlayerPosition(map, playerRect);
}

void mapCanvas (int i, tmx_map *map){
    map = GetMap(i);

	if (!map) {
		tmx_perror("Cannot load map");
        return;
	}
    
    render_map(map);
}

//quando tentei colocar no lugar certo (game.c), bugou tudo, então deixei aqui mesmo, tudo que ta aqui é de lá

void PlayerControl(Rectangle *playerRect, tmx_map *map)
{
    Rectangle auxu = *playerRect;
    auxu.y -= 5;
    Rectangle auxd = *playerRect;
    auxd.y += 5;
    Rectangle auxl = *playerRect;
    auxl.x -= 5;
    Rectangle auxr = *playerRect;
    auxr.x += 5;
    if (IsKeyDown(KEY_UP) && !CheckObjgr(map, &auxu, "Paredes"))
    {
        playerRect->y -= 4; 
    }
    else if (IsKeyDown(KEY_UP) && CheckObjgr(map, &auxu, "Paredes"))
    {
        playerRect->y += 1;
    }
    if (IsKeyDown(KEY_DOWN) && !CheckObjgr(map, &auxd, "Paredes"))
    {
        playerRect->y += 4;
    }
    else if(IsKeyDown(KEY_DOWN) && CheckObjgr(map, &auxd, "Paredes"))
    {
        playerRect->y -= 1;
    }
    if (IsKeyDown(KEY_LEFT) && !CheckObjgr(map, &auxl, "Paredes"))
    {
        playerRect->x -= 4;
    }
    else if(IsKeyDown(KEY_LEFT) && CheckObjgr(map, &auxl, "Paredes"))
    {
        playerRect->x += 1;
    }
    if (IsKeyDown(KEY_RIGHT) && !CheckObjgr(map, &auxr, "Paredes"))
    {
        playerRect->x += 4;
    }
    else if(IsKeyDown(KEY_RIGHT) && CheckObjgr(map, &auxr, "Paredes"))
    {
        playerRect->x -= 1;
    }
}

#include "canvas.h"
#include "railyb.h"
#define WHITE      (Color){ 255, 255, 255, 255 }

void Creditos(){
    BeginDrawing();
    ClearBackGround(Black);
    DrawPropCenteredText("Créditos:", 0.1, 0.1, 24, WHITE);
     DrawPropCenteredText("Grupo 7", 0.1, 0.2, WHITE);
     DrawPropCenteredText("João Miguel", 0.1, 0.3, WHITE);
     DrawPropCenteredText("Heitor Melo", 0.1, 0.4, WHITE);
     DrawPropCenteredText("Henrique Cesar", 0.1, 0.5, WHITE);
     DrawPropCenteredText("Rodrigo Sampaio", 0.1, 0.6, WHITE);
     DrawPropCenteredText("Milena Neves", 0.1, 0.7, WHITE);
     DrawPropCenteredText("Isabela Lima", 0.1, 0.8, WHITE);
    EndDrawing();
}

