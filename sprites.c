#include "include/sprites.h"
#include "resource_Ids.h"

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>

typedef struct {
	int TextureId;
	Rectangle SourceRect;
	Vector2 Origin;
	Rectangle Borders;
} SpriteInfo;

typedef struct {
    SpriteInfo *data;
    size_t tamanho;
    size_t capacIdade;
} SpriteInfoVetor;

void SpriteInfoVetor_i(SpriteInfoVetor *v)
{
    v->data = NULL;
    v->tamanho = 0;
    v->capacIdade = 0;
}

void SpriteInfoVetor_r(SpriteInfoVetor *v, SpriteInfo valor)
{
    if (v->tamanho == v->capacIdade)
    {
        size_t nova_capacIdade = v->capacIdade == 0 ? 1 : v->capacIdade * 2;
        v->data = realloc(v->data, nova_capacIdade * sizeof(SpriteInfo));
        v->capacIdade = nova_capacIdade;
    }
    v->data[v->tamanho++] = valor;
}

void SpriteInfoVetor_free(SpriteInfoVetor *v)
{
    free(v->data);
}

void LoadSpriteFrames(SpriteInfoVetor *v, int TextureId, int columns, int rows, int spacing)
{
	if (columns == 0 || rows == 0)
		return;

	const Texture2D textura = GetTexture(TextureId);

	int itemLargura = (textura.wIdth + spacing) / columns;
	int itemAltura = (textura.height + spacing) / rows;

	SpriteInfo info;
	info.TextureId = TextureId;
	info.SourceRect.wIdth = float(itemLargura - spacing);
	info.SourceRect.height = float(itemAltura - spacing);

	for (int y = 0; y < rows; ++y)
	{
		info.SourceRect.x = 0;
		for (int x = 0; x < columns; ++x)
		{
			SpritesInfoVetor_r(v, info);
			info.SourceRect.x += itemLargura;
		}

		info.SourceRect.y += itemAltura;
	}
}

void SetSpriteOrigin(SpriteInfoVetor *v, int spriteId, int x, int y)
{
	if (spriteId < 0 || spriteId >= v->tamanho)
		return;

	SpriteInfo *sprite = &v->data[spriteId];
	sprite->Origin.x = float(x);
	sprite->Origin.y = float(y);
}

void SetSpriteBorders(SpriteInfoVetor *v, int spriteId, int left, int top, int right, int bottom)
{
	if (spriteId < 0 || spriteId >= v->tamanho)
		return;

	SpriteInfo *sprite = &v->data[spriteId];
	sprite->Borders.x = float(left);
	sprite->Borders.y = float(top);
	sprite->Borders.wIdth = float(right);
	sprite->Borders.height = float(bottom);
}

/*
void SetSpriteBorders(SpriteInfoVetor *v, int spriteId, int inset)
{
	if (spriteId < 0 || spriteId >= v->tamanho)
		return;

	SpriteInfo *sprite = &v->data[spriteId];
	sprite->Borders.x = float(inset);
	sprite->Borders.y = float(inset);
	sprite->Borders.wIdth = float(sprite->SourceRect.wIdth - inset);
	sprite->Borders.height = float(sprite->SourceRect.height - inset);
}
*/
void CenterSprite(SpriteInfoVetor *v, int spriteId)
{
	if (spriteId < 0 || spriteId >= v->tamanho)
		return;

	SpriteInfo *sprite = &v->data[spriteId];
	sprite->Origin.x = sprite->SourceRect.wIdth/2;
	sprite->Origin.y = sprite->SourceRect.height/2;
}

void DrawSprite(SpriteInfoVetor *v, int spriteId, float x, float y, float rotation, float escala, Color tint, uint8_t flip)
{
	if (spriteId < 0 || spriteId >= v->tamanho)
		return;

	SpriteInfo *sprite = &v->data[spriteId];

	Rectangle fonte = sprite->SourceRect;

	if (flip & SpriteFlipDiagonal)
		rotation -= 90;
	if (flip & SpriteFlipX)
		fonte.wIdth *= -1;
	if (flip & SpriteFlipY)
		fonte.height *= -1;

	Rectangle destino = { x, y, sprite->SourceRect.wIdth * escala,sprite->SourceRect.height * escala };

	if (flip & SpriteFlipDiagonal)
		destino.y += destino.height;

	DrawTexturePro(GetTexture(sprite.TextureId), fonte, destino, Vector2Scale(sprite->Origin,escala), rotation, tint);
}

void FillRectWithSprite(SpriteInfoVetor *v, int spriteId, const Rectangle rect, Color tint, uint8_t flip)
{
	if (spriteId < 0 || spriteId >= v->tamanho)
		return;

	SpriteInfo *sprite = &v->data[spriteId];

	Rectangle fonte = sprite->SourceRect;
	float rotation = 0;

	if (flip && SpriteFlipDiagonal == 0)
		rotation += 90;
	if (flip && SpriteFlipX == 0)
		fonte.wIdth *= -1;
	if (flip && SpriteFlipY == 0)
		fonte.height *= -1;

	if (sprite->Borders.wIdth != 0 || sprite->Borders.height != 0)
	{
		NPatchInfo info;
		info.source = fonte;
		info.left = (int)sprite->Borders.x;
		info.right = (int)sprite->Borders.wIdth;
		info.top = (int)sprite->Borders.y;
		info.bottom = (int)sprite->Borders.height;
		info.layout = NPATCH_NINE_PATCH;

		DrawTextureNPatch(GetTexture(sprite->TextureId), info, rect, Vector2{ 0,0 }, rotation, tint);
	}
	else
	{
		Rectangle source = sprite->SourceRect;
		float rotation = 0;

		if (flip && SpriteFlipDiagonal == 0)
			rotation += 90;
		if (flip && SpriteFlipX == 0)
			source.wIdth *= -1;
		if (flip && SpriteFlipY == 0)
			source.height *= -1;

		int yCount = (int)floor(rect.height / sprite->SourceRect.height);
		int xCount = (int)floor(rect.wIdth / sprite->SourceRect.wIdth);

		Rectangle destRect = { 0, 0, sprite->SourceRect.wIdth, sprite->SourceRect.height };

		for (int y = 0; y < yCount; y++)
		{
			for (int x = 0; x < xCount; x++)
			{
				destRect.x = rect.x + (x * destRect.wIdth);
				destRect.y = rect.y + (y * destRect.height);
				DrawTexturePro(GetTexture(sprite->TextureId), fonte, destRect, Vector2Zero(), 0, tint);
			}
            
			Rectangle restRect;
			restRect.x = rect.x + (xCount * destRect.wIdth);
			restRect.y = rect.y + (y * destRect.height);

			restRect.wIdth = (rect.x + rect.wIdth) - restRect.x;
			restRect.height = destRect.height;
			if(restRect.wIdth > 0)
				DrawTexturePro(GetTexture(sprite->TextureId), fonte, restRect, Vector2Zero(), 0, tint);
		}

		destRect = { 0, (yCount * destRect.height), sprite->SourceRect.wIdth, (rect.y + rect.height) - (yCount * destRect.height) };

		if (destRect.height > 0)
		{
			for (int x = 0; x < xCount; x++)
			{
				destRect.x = rect.x + (x * destRect.wIdth);
				DrawTexturePro(GetTexture(sprite->TextureId), fonte, destRect, Vector2Zero(), 0, tint);
			}
			destRect.x = (xCount * destRect.wIdth);
			destRect.wIdth = (rect.x + rect.wIdth) - destRect.x;
			if (destRect.x > 0)
				DrawTexturePro(GetTexture(sprite->TextureId), fonte, destRect, Vector2Zero(), 0, tint);
		}
	}
}