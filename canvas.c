#include "raylib.h"
#include "canvas.h"

void DrawFixedPropRectangle(float xProp, float yProp, float wProp, float hProp, Color color){
    DrawRectangle(GetScreenWidth() * xProp, GetScreenHeight() * yProp, GetScreenWidth() * wProp, GetScreenHeight() * hProp, color);
}
void DrawFixedPropCircle(float xProp, float yProp, float rProp, Color color){
    DrawCircle(GetScreenWidth() * xProp, GetScreenHeight() * yProp, GetScreenWidth() * rProp, color);
}
void DrawFixedPropText(const char *text, float xProp, float yProp, float fontSizeProp, Color color){
    DrawText(text, GetScreenWidth() * xProp, GetScreenHeight() * yProp, (int) (GetScreenHeight() * fontSizeProp), color);
}


void DrawPropCenteredTexture(Texture2D texture, float xProp, float yProp, Color tint){
    DrawTexture(texture, GetScreenWidth() * xProp - texture.width / 2, GetScreenHeight() * yProp - texture.height / 2, tint);
}
void DrawPropCenteredText(const char *text, float xProp, float yProp, int fontSize, Color color){
    DrawText(text, GetScreenWidth() * xProp - MeasureText(text, fontSize) / 2.0, GetScreenHeight() * yProp - fontSize / 2.0, fontSize, color);
}
void DrawPropCenteredRectangle(float xProp, float yProp, float width, float height, Color color){
    DrawRectangle(GetScreenWidth() * xProp - width / 2, GetScreenHeight() * yProp - height / 2, width, height, color);
}

void DrawPropResCenteredTexture(Texture2D texture, Vector2 proportions, float rotation, float scale, Color tint){
    DrawTextureEx(texture, (Vector2){GetScreenWidth() * proportions.x - texture.width * scale / 2, GetScreenHeight() * proportions.y - texture.height * scale / 2}, rotation, scale, tint);
}


void DrawPropTexture(Texture2D texture, float xProp, float yProp, Color tint){
    DrawTexture(texture, GetScreenWidth() * xProp, GetScreenHeight() * yProp, tint);
}
void DrawCenteredText(const char *text, int posX, int posY, int fontSize, Color color){
    DrawText(text, posX - MeasureText(text, fontSize) / 2.0, posY - fontSize / 2.0, fontSize, color);
}
void DrawPropCircle(float xProp, float yProp, float radius, Color color){
    DrawCircle(GetScreenWidth() * xProp, GetScreenHeight() * yProp, radius, color);
}
void DrawPropRectangle(float xProp, float yProp, float width, float height, Color color){
    DrawRectangle(GetScreenWidth() * xProp, GetScreenHeight() * yProp, width, height, color);
}


void DrawPropText(const char *text, float xProp, float yProp, int fontSize, Color color){
    DrawText(text, GetScreenWidth() * xProp, GetScreenHeight() * yProp, fontSize, color);
}
void DrawCenteredTexture(Texture2D texture, int posX, int posY, Color tint){
    DrawTexture(texture, posX - texture.width / 2, posY - texture.height / 2, tint);
}
void DrawCenteredRectangle(int posX, int posY, int width, int height, Color color){
    DrawRectangle(posX - width / 2, posY - height / 2, width, height, color);
}
