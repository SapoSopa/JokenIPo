#include "tile_map.h"
#include "sprites.h"

Rectangle CurrentViewRect = { 0 };

Rectangle GetTileDisplayRect(int x, int y, bool orthographic, const Vector2& tileSize)
{
	if (orthographic)
	{
        Rectangle rect = {(float)(x * tileSize.x), (float)(y * tileSize.y), tileSize.x, tileSize.y };
        return rect;
    }
	
    float halfWidth = tileSize.x * 0.5f;
	float halfHeight = tileSize.y * 0.5f;
	float quarterHeight = tileSize.y * 0.25f;
    
	Rectangle rect = { x * halfWidth - y * halfWidth - halfWidth, y * halfHeight + (x * halfHeight), tileSize.x, tileSize.y };
    return rect;
}

const Tile* GetTile(int x, int y, const TileLayer *layer)
{
	if (x < 0 || y < 0 || x >= layer.Size.x || y >= layer.Size.y)
		return NULL;

	return &layer.Tiles[y * (int)layer.Size.x + x];
}

bool RectInView(const Rectangle *rect)
{
	if (rect.x + rect.width < CurrentViewRect.x)
		return false;

	if (rect.y + rect.height < CurrentViewRect.y)
		return false;

	if (rect.x > CurrentViewRect.x + CurrentViewRect.width)
		return false;

	if (rect.y > CurrentViewRect.y + CurrentViewRect.height)
		return false;

	return true;
}

void DrawTileMap(Camera2D *camera, const TileMap *map)
{
	CurrentViewRect.x = camera.target.x - (camera.offset.x / camera.zoom);
	CurrentViewRect.y = camera.target.y - (camera.offset.y / camera.zoom);

	CurrentViewRect.width = GetScreenWidth() / camera.zoom;
	CurrentViewRect.height = GetScreenHeight() / camera.zoom;

	for (int i = 0; i < map.Layers.size; i++)
	{
        const Layer* layer = map.Layers[i];
		if (layer->IsObject)
		{
			const ObjectLayer* objectLayer = (const ObjectLayer*)layer;

			for (int j = 0; j < objectLayer->Objects.size; j++)
			{
                const TileObject* object = objectLayer->Objects[j];
				if (object->SubType == TileObject_SubTypes_Text)
				{
					const TileTextObject* textObject = (const TileTextObject*)object;
					DrawText(textObject->Text, (int)textObject->Bounds.x, (int)textObject->Bounds.y, textObject->FontSize, textObject->TextColor);
				}
			}
		}
		else
		{
			const TileLayer* tileLayer = (const TileLayer*)layer;

			for (int y = 0; y < (int)tileLayer->Size.y; ++y)
			{
				for (int x = 0; x < (int)tileLayer->Size.x; ++x)
				{
					Rectangle destinationRect = GetTileDisplayRect(x, y, map.MapType == TileMapTypes_Orthographic, tileLayer.TileSize);
					if (!RectInView(destinationRect))
						continue;

					const Tile* tile = GetTile(x, y, *tileLayer);
					if (tile == NULL)
						continue;
					DrawSprite(tile->Sprite, destinationRect.x, destinationRect.y, 0, 1, WHITE, tile->Flip);
				}
			}
		}
	}
}