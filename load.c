#include "include/load.h"
#include "include/audio.h"
#include "include/config.h"
#include "include/items.h"
#include "include/game.h"

#include "stdlib.h"
#include "raylib.h"


#define TO_LOAD_TEXTURES 3
#define TO_LOAD_SOUNDS 3
#define TO_LOAD_MUSICS 3

static char texturesToLoad[TO_LOAD_TEXTURES][100] = {
    "assets/textures/texture1.png",
    "assets/textures/texture2.png",
    "assets/textures/texture3.png"
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

float loadProgress = 0.0f;
int loadStatus = 0;
char loadingStatus[5][100] = {"Loading...", "Loading textures...", "Loading sounds...", "Loading musics...", "Loading config..."};

int GetTexture_Idx(char *name) {
    return -1;
}

void LoadConfig() {
}
void LoadTexts() {
}
void M_LoadTexture() {
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
void UnloadAll() {
    UnloadAll_Audio();
}
