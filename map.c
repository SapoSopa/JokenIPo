
#include "include/map.h"
#include "include/config.h"
#include "include/resourcesIdx.h"
#include "include/canvas.h"
#include "include/game.h"

#include "raylib.h"
#include "tmx.h"

static tmx_map *CurrentMap = NULL;

tmx_map* GetCurrentMap()
{
    return CurrentMap;
}

void SetCurrentMap(tmx_map *map)
{
    CurrentMap = map;
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
    if (!map || !playerRect)
        return;

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
                            playerRect->x = obj->x - playerRect->width/2;
                            playerRect->y = obj->y - playerRect->height;
                            achou = true;
                            printf("posição x,y: %f,%f\n", playerRect->x, playerRect->y);
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
    char portas [11][20] = {"Porta_I", "Porta_II", "Porta_III", "Porta_IV", "Porta_V", "Porta_VI", 
                            "Porta_VII", "Porta_VIII", "Porta_IX", "Porta_X", "Porta_XI"};
    
    for (int i = 0; i < 11; i++){
        if (CheckObjName(map, playerRect, "Portas", portas[i]))
        {
            return Porta_I + i;
        }
    }

    return -1;
    
}

void UpdateMap(tmx_map *map, Rectangle *playerRect)
{
    int currentMap = CheckWhereToGo(map, playerRect);
    map = GetMap(currentMap);
    SetCurrentMap(map);
    UpdatePlayerPosition(map, playerRect);
}

void UpdateEnemiesSprites(){

}