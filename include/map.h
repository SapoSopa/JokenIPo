#pragma once
#include "tmx.h"
#include "raylib.h"

tmx_map* GetCurrentMap();
void SetCurrentMap(tmx_map *map);

bool CheckObjName(tmx_map *map, Rectangle *playerRect, char *name, char *objName);
bool CheckObjgr(tmx_map *map, Rectangle *playerRect, char *name);
void UpdatePlayerPosition(tmx_map *map, Rectangle *playerRect);

int CheckWhereToGo (tmx_map *map, Rectangle *playerRect);
void UpdateMap(tmx_map *map, Rectangle *playerRect);

void PlayerControl(Rectangle *playerRect, tmx_map *map);