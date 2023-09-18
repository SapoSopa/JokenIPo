#pragma once

#include "raylib.h"

void DrawFixedPropRectangle(float xProp, float yProp, float wProp, float hProp, Color color);
void DrawFixedPropCircle(float xProp, float yProp, float rProp, Color color);
void DrawFixedPropText(const char *text, float xProp, float yProp, float fontSizeProp, Color color);

void DrawPropCenteredTexture(Texture2D texture, float xProp, float yProp, Color tint);
void DrawPropCenteredText(const char *text, float xProp, float yProp, int fontSize, Color color);
void DrawPropCenteredRectangle(float xProp, float yProp, float width, float height, Color color);

void DrawPropTexture(Texture2D texture, float xProp, float yProp, Color tint);
void DrawPropText(const char *text, float xProp, float yProp, int fontSize, Color color);
void DrawPropCircle(float xProp, float yProp, float radius, Color color);
void DrawPropRectangle(float xProp, float yProp, float width, float height, Color color);

void DrawCenteredText(const char *text, int posX, int posY, int fontSize, Color color);
void DrawCenteredTexture(Texture2D texture, int posX, int posY, Color tint);
void DrawCenteredRectangle(int posX, int posY, int width, int height, Color color);
