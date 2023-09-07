#pragma once

#include "raylib.h"
#include "tile_map.h"

#include <stdlib.h>

void LoadMap(const char* file);
void ClearMap();
void DrawMap();

TileObject** GetMapObjectsOfType(const char* objType, TileObject.SubTypes requiredType, int count);
TileObject* GetFirstMapObjectOfType(const char* objType, TileObject.SubTypes requiredType);

bool PointInMap(const Vector2 *point);
bool Ray2DHitsMap(const Vector2 *startPoint, const Vector2 *endPoint);

typedef struct {
	int Id;
	bool Active;
	int SpriteFrame;
	Vector2 Position;
	Color Tint;
	bool Bobble;
	bool Shadow;
}  SpriteInstance;

SpriteInstance* AddSprite(int frame, const Vector2 *position);
void UpdateSprite(int spriteId, const Vector2 *position);
void RemoveSprite(SpriteInstance* sprite);
void RemoveSprite(int id);
void ClearSprites();

typedef enum {
	Fade,
	RiseFade,
	RotateFade,
	ScaleFade,
	ToTarget,
}  EffectType;
//void AddEffect(const Vector2 *position, EffectType effect, int spriteId, float lifetime);
//void AddEffect(const Vector2 *position, EffectType effect, int spriteId, const Vector2 *target, float lifetime);

#define PlayerSpawnType "player_spawn"
#define MobSpawnType "mob_spawn"
#define ChestType "chest"
#define ExitType "exit"