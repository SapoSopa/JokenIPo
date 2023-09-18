#include "include/load.h"
#include "include/audio.h"
#include "include/config.h"
#include "include/items.h"
#include "include/game.h"
#include "include/sprites.h"
#include "tmx.h"

#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"

#define TO_LOAD_TEXTURES 1
#define TO_LOAD_SOUNDS 3
#define TO_LOAD_MUSICS 3
#define TO_LOAD_MAPS 4

static Texture GameTextures[TO_LOAD_TEXTURES];
static Sound GameSounds[TO_LOAD_SOUNDS];
static Music GameMusics[TO_LOAD_MUSICS];
static tmx_map* GameMaps[TO_LOAD_MAPS];

//remember to add in resourcesIdx too
static char texturesToLoad[TO_LOAD_TEXTURES][100] = {
    "assets/textures/torre.png",
};
static char soundsToLoad[TO_LOAD_SOUNDS][100] = {
    "assets/sounds/sound1.wav",
    "assets/sounds/sound2.wav",
    "assets/sounds/sound3.wav"
};
static char musicsToLoad[TO_LOAD_MUSICS][100] = {
    "assets/musics/music1.ogg",
    "assets/musics/music2.ogg",
    "assets/musics/music3.ogg"
};
static char mapsToLoad[TO_LOAD_MAPS][100] = {
    "assets/tilemaps/map.tmx",
    "assets/tilemaps/map1.tmx",
    "assets/tilemaps/map2.tmx",
    "assets/tilemaps/map3.tmx",
    "assets/tilemaps/map4.tmx"
};

float loadProgress = 0.0f;
int loadStatus = 0;
char loadingStatus[5][100] = {"Loading...", "Loading textures...", "Loading sounds...", "Loading musics...", "Loading config..."};

tmx_map* GetMap(int map) {
    if (map < 0 || map >= TO_LOAD_MAPS) 
        return NULL;
    return GameMaps[map];
}

Texture* GetTexture(int texture) {
    if (texture < 0 || texture >= TO_LOAD_TEXTURES) 
        return NULL;
    return &GameTextures[texture];
}

void LoadConfig() {
}
void LoadTexts() {
}
void M_LoadMap() {
    tmx_img_load_func = raylib_tex_loader;
    tmx_img_free_func = raylib_free_tex;;
    for (int i = 0; i < TO_LOAD_MAPS; i++) {
        GameMaps[i] = tmx_load(mapsToLoad[i]);
        if (GameMaps[i] == NULL){
            printf("Error loading map %d\n", i);
            loadStatus = -1;
            return;
        }
        loadProgress += 1.0f / (TO_LOAD_TEXTURES + TO_LOAD_SOUNDS + TO_LOAD_MUSICS + TO_LOAD_MAPS + 1);
    }
}
void M_LoadTexture() {
    for (int i = 0; i < TO_LOAD_TEXTURES; i++) {
        GameTextures[i] = LoadTexture(texturesToLoad[i]);
        loadProgress += 1.0f / (TO_LOAD_TEXTURES + TO_LOAD_SOUNDS + TO_LOAD_MUSICS + TO_LOAD_MAPS + 1);
    }
}

void ToLoadTextures() {
}
void ToLoadSounds() {
    LoadSoundFile("/assets/audios/sounds.txt");
}
void ToLoadMusics() {
    LoadMusicFile("/assets/audios/musics.txt");
}

int SaveGame() {
    return 0;
}
int LoadGame() {
    return 0;
}

float UpdateLoadAll() {
    return 0.0f;
}
char* LoadingStatus() {
    return loadingStatus[loadStatus];
}
void UnloadResources() {
    for (int i = 0; i < TO_LOAD_TEXTURES; i++) {
        UnloadTexture(GameTextures[i]);
    }

    UnloadAll_Audio();
}
