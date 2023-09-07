#pragma once

#include "raylib.h"

#include <stdint.h>

#define SpriteFlipNone 0
#define SpriteFlipX 0x02
#define SpriteFlipY 0x04
#define SpriteFlipDiagonal 0x08

void LoadSpriteFrames(int textureId, int colums, int rows, int spacing);
void SetSpriteOrigin(int spriteId, int x, int y);
void SetSpriteBorders(int spriteId, int left, int top, int right, int bottom);
//void SetSpriteBorders(int spriteId, int inset);
void CenterSprite(int spriteId);

void DrawSprite(int spriteId, float x, float y, float rotation, float scale, Color tint, uint8_t flip);
void FillRectWithSprite(int spriteId, const Rectangle *rect, Color tint, uint8_t flip);