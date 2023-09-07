#pragma once

#include "sprites.h"

#include "raylib.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
	Orthographic,
	Isometric,
} TileMapTypes;

typedef struct {
	int16_t Sprite;
	uint8_t Flip;
} Tile;

typedef struct {
	int Id;
	char Name[100];
	Vector2 Size;
	int IsObject;
} Layer;

typedef struct {
    Layer base;
	Vector2 TileSize;
    Tile *Tiles;
	size_t TilesCount;
} TileLayer;

typedef struct {
	char Name[100];
	char Type[100];
	char Value[100];
} Property;

int Property_GetInt(const Property *p)
{
    if (strcmp(p->Type, "int") != 0 || strlen(p->Value) == 0)
        return 0;
    return atoi(p->Value);
}

float Property_GetFloat(const Property *p)
{
    if (strcmp(p->Type, "float") != 0 || strlen(p->Value) == 0)
        return 0;

    return atof(p->Value);
}

const char* Property_GetString(const Property *p)
{
    return p->Value;
}

typedef struct {
	int ID;
	char Name[100];
	Rectangle Bounds;
	int Visible;
	char Type[100];
	float Rotation;
	int GridTile;
	char Template[100];
	enum SubTypes {
		None,
		Ellipse,
		Point,
		Polygon,
		Polyline,
		Text,
	} SubType;
    Property *Properties;
    size_t PropertiesCount;
} TileObject;

const Property* TileObject_GetProperty(const TileObject *obj, const char *name)
{
    for (size_t i = 0; i < obj->PropertiesCount; i++)
    {
        if (strcmp(obj->Properties[i].Name, name) == 0)
            return &obj->Properties[i];
    }
    return NULL;
}

typedef struct {
    TileObject base;
	Vector2 *Points;
    size_t PointsCount;
} TilePolygonObject;

typedef struct {
    TileObject base;
	char Text[100];
	Color TextColor;
	int Wrap;
	int FontSize;
	char FontFamily[100];
	int Bold;
	int Italic;
	int Underline;
	int Strikeout;
	int Kerning;
	char HorizontalAlignment[10];
	char VerticalAlignment[10];
} TileTextObject;

typedef struct {
    Layer base;
	TileObject **Objects;
    size_t ObjectCount;
} ObjectLayer;

typedef struct {
	TileMapTypes MapType;
	Layer **Layers;
    size_t LayersCount;
	TileLayer **TileLayers;
    size_t TileLayersCount;
	ObjectLayer **ObjectLayers;
    size_t ObjectLayersCount;
	Property **Properties;
    size_t PropertiesCount;
} TileMap;

const Property* TileMap_GetProperty(const TileMap *map, const char *name)
{
    for (size_t i = 0; i < map->PropertiesCount; i++)
    {
        if (strcmp(map->Properties[i]->Name, name) == 0)
            return &map->Properties[i];
    }
    return NULL;
}

bool ReadTileMap(const char* filePath, TileMap *map);

void DrawTileMap(Camera2D *camera, const TileMap *map);