#include "map.h"

#include "resource_ids.h"
#include "sprites.h"
#include "tile_map.h"
#include "audio.h"

#include "raylib.h"
#include "raymath.h"

#include <math.h>
#include <unordered_map>
#include <list>

typedef struct {
    Vector2 Position;
    EffectType Effect;
    int SpriteId;
    float Lifetime;
    float MaxLifetime;
    Vector2 Target;
} EffectInstance;

EffectInstance Effects[100];
int EffectsCount = 0;

Rectangle VisibilityInset = { 200, 200, 200, 250 };
Camera2D MapCamera = { 0 };

TileMap CurrentMap;
typedef struct {
    int id;
    SpriteInstance sprite;
} SpriteEntry;

SpriteEntry SpriteInstances[100];
int SpriteInstancesCount = 0;
int NextSpriteId = 0;

Rectangle MapBounds = { 0, 0, 0, 0 };

bool PointInMap(Vector2 point)
{
	if (!CheckCollisionPointRec(point, MapBounds))
		return false;
	for (int i = 0; i < CurrentMap.ObjectLayersCount; i++)
	{
        ObjectLayer *layerInfo = CurrentMap.ObjectLayers[i];
        
		for (int j = 0; j < layerInfo.ObjectCount; j++)
		{
            TileObject *object = layerInfo.Objects[j];
			if (strcmp(object->Type, "wall") == 0)
			{
				if (CheckCollisionPointRec(point, object->Bounds))
					return false;
			}
		}
	}

	return true;
}

bool CheckCollisionLineRec(const Vector2 *startPoint, const Vector2 *endPoint, const Rectangle *rectangle)
{
	// ether point is in the rectangle
	if (CheckCollisionPointRec(startPoint, rectangle) || CheckCollisionPointRec(endPoint, rectangle))
		return true;

	// top
	if (CheckCollisionLines(startPoint, endPoint, Vector2{ rectangle.x,rectangle.y }, Vector2{ rectangle.x + rectangle.width, rectangle.y }, nullptr))
		return true;

	// right
	if (CheckCollisionLines(startPoint, endPoint, Vector2{ rectangle.x + rectangle.width,rectangle.y }, Vector2{ rectangle.x + rectangle.width, rectangle.y + rectangle.height }, nullptr))
		return true;

	// bottom
	if (CheckCollisionLines(startPoint, endPoint, Vector2{ rectangle.x, rectangle.y + rectangle.height }, Vector2{ rectangle.x + rectangle.width, rectangle.y + rectangle.height }, nullptr))
		return true;

	// left
	if (CheckCollisionLines(startPoint, endPoint, Vector2{ rectangle.x,rectangle.y }, Vector2{ rectangle.x, rectangle.y + rectangle.height }, nullptr))
		return true;

	return false;
}

bool Ray2DHitsMap(const Vector2 *startPoint, const Vector2 *endPoint)
{
	if (!PointInMap(startPoint) || !PointInMap(endPoint))
		return true;

	for (int i = 0; i < CurrentMap.ObjectLayersCount; i++)
	{
        ObjectLayer *layerInfo = CurrentMap.ObjectLayers[i];
        
		for (int j = 0; j < layerInfo.ObjectCount; j++)
		{
            TileObject *object = layerInfo.Objects[j];
			if (strcmp(object->Type, "wall") == 0)
			{
				if (CheckCollisionLineRec(startPoint, endPoint, object->Bounds))
					return true;
			}
		}
	}

	return false;
}

void LoadMap(const char* file)
{
	ClearSprites();
	ReadTileMap(file, CurrentMap);

	MapCamera.offset.x = GetScreenWidth() * 0.5f;
	MapCamera.offset.y = GetScreenHeight() * 0.5f;

	MapCamera.rotation = 0;
	MapCamera.zoom = 1;

	MapCamera.target.x = 0;
	MapCamera.target.y = 0;

	MapBounds = Rectangle{ 0,0,0,0 };

	if (!CurrentMap.TileLayersCount > 0)
	{
		int index = CurrentMap.TileLayersCount - 1;

		MapBounds.width = (CurrentMap.TileLayers[index]->Size.x * CurrentMap.TileLayers[index]->TileSize.x);
		MapBounds.height = (CurrentMap.TileLayers[index]->Size.y * CurrentMap.TileLayers[index]->TileSize.y);

		MapCamera.target.x = MapBounds.width / 2;
		MapCamera.target.y = MapBounds.height / 2;
	}
//audio
	const Property* bgm = CurrentMap.GetProperty("bgm");
	if (bgm)
	{
		StopBGM();
		StartBGM(bgm->GetString());
	}
}

void ClearMap()
{
	CurrentMap.ObjectLayersCount = 0;
	CurrentMap.TileLayersCount = 0;
	ClearSprites();
	EffectsCount = 0;
}

void DrawMap() {
    if (CurrentMap.TileLayersCount == 0)
        return;

    BeginMode2D(GetMapCamera());
    DrawTileMap(MapCamera, CurrentMap);

    for (int i = 0; i < SpriteInstancesCount; i++) {
        SpriteInstance sprite = SpriteInstances[i].sprite;
        if (sprite.Active) {
            float offset = 0;
            if (sprite.Bobble)
                offset = fabsf(sinf(GetTime() * 5) * 3);

            if (sprite.Shadow)
                DrawSprite(sprite.SpriteFrame, sprite.Position.x + 2, sprite.Position.y + 2 + offset, 0.0f, 1.0f, ColorAlpha(BLACK, 0.5f));

            DrawSprite(sprite.SpriteFrame, sprite.Position.x, sprite.Position.y + offset, 0.0f, 1.0f, sprite.Tint);
        }
    }

    for (int i = 0; i < EffectsCount; i++) {
        EffectInstance* effect = &Effects[i];
        effect->Lifetime -= GetFrameTime();

        if (effect->Lifetime < 0) {
            // Remover o efeito da lista
            EffectsCount--;
            for (int j = i; j < EffectsCount; j++)
                Effects[j] = Effects[j + 1];
            i--;
            continue;
        }

        float param = effect->Lifetime / effect->MaxLifetime;
        float rotation = 0;
        float alpha = 1;
        float scale = 1;

        Vector2 pos = effect->Position;

        switch (effect->Effect) {
            case Fade:
                alpha = param;
                break;

            case RiseFade:
                alpha = param;
                pos.y -= (1.0f - param) * 30;
                break;

            case RotateFade:
                rotation = (1.0f - param) * 360;
                alpha = param;
                break;

            case ScaleFade:
                alpha = param;
                scale = 1 + (1.0f - param);
                break;

            case ToTarget: {
                Vector2 vec = Vector2Subtract(effect->Target, effect->Position);
                float dist = Vector2Length(vec);
                vec = Vector2Normalize(vec);

                pos = Vector2Add(effect->Position, Vector2Scale(vec, dist * (1.0f - param)));
                break;
            }
        }

        DrawSprite(effect->SpriteId, pos.x, pos.y, rotation, scale, ColorAlpha(WHITE, alpha));
    }

    EndMode2D();
}


int GetMapObjectsOfType(const char* objType, TileObjectSubTypes requiredType, const TileObject** objects) {
    int count = 0;
    if (CurrentMap.ObjectLayersCount == 0)
        return count;

    for (int i = 0; i < CurrentMap.ObjectLayersCount; i++) {
        LayerInfo layerInfo = CurrentMap.ObjectLayers[i];
        for (int j = 0; j < layerInfo.ObjectsCount; j++) {
            const TileObject* object = layerInfo.Objects[j];
            if (strcmp(object->Type, objType) == 0 && (requiredType == None || object->SubType == requiredType)) {
                objects[count++] = object;
            }
        }
    }

    return count;
}


const TileObject* GetFirstMapObjectOfType(const char* objType, TileObjectSubTypes requiredType) {
    if (CurrentMap.ObjectLayersCount == 0)
        return NULL;

    for (int i = 0; i < CurrentMap.ObjectLayersCount; i++) {
        LayerInfo layerInfo = CurrentMap.ObjectLayers[i];
        for (int j = 0; j < layerInfo.ObjectsCount; j++) {
            const TileObject* object = layerInfo.Objects[j];
            if (strcmp(object->Type, objType) == 0 && (requiredType == None || object->SubType == requiredType))
                return object;
        }
    }

    return NULL;
}

SpriteInstance* AddSprite(int frame, Vector2 position) {
    NextSpriteId++;
    SpriteInstances[NextSpriteId] = (SpriteInstance){ NextSpriteId, 1, frame, position };
    return &SpriteInstances[NextSpriteId];
}

void UpdateSprite(int spriteId, Vector2 position) {
    if (SpriteInstances[spriteId].Id != spriteId)
        return;

    SpriteInstances[spriteId].Position = position;
}

void RemoveSprite(SpriteInstance* sprite) {
    if (sprite != NULL)
        RemoveSprite(sprite->Id);
}

void RemoveSprite(int spriteId) {
    if (SpriteInstances[spriteId].Id != spriteId)
        return;

    SpriteInstances[spriteId] = (SpriteInstance){ 0 };
}

void ClearSprites() {
    for (int i = 0; i <= NextSpriteId; i++)
        SpriteInstances[i] = (SpriteInstance){ 0 };
    NextSpriteId = 0;
}

void AddEffect(Vector2 position, EffectType effect, int spriteId, float lifetime) {
    CenterSprite(spriteId);
    Effects[EffectsCount++] = (EffectInstance){ position, effect, spriteId, lifetime, lifetime };
}

void AddEffect(Vector2 position, EffectType effect, int spriteId, Vector2 target, float lifetime) {
    CenterSprite(spriteId);
    Effects[EffectsCount++] = (EffectInstance){ position, effect, spriteId, lifetime, lifetime, target };
}
