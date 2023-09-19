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

#define TO_LOAD_TEXTURES 19
#define TO_LOAD_SOUNDS 11
#define TO_LOAD_MUSICS 7
#define TO_LOAD_MAPS 11


static Texture GameTextures[TO_LOAD_TEXTURES];
static Sound GameSounds[TO_LOAD_SOUNDS];
static Music GameMusics[TO_LOAD_MUSICS];
static tmx_map* GameMaps[TO_LOAD_MAPS];
/* Rock,
    Fire,
    Scissors,
    Human,
    Sponge,
    Paper,
    Air,
    Water,
    Gun, */
//remember to add in resourcesIdx too
static char texturesToLoad[TO_LOAD_TEXTURES][100] = {
    "assets/textures/torre.png",
    "assets/textures/rock.png",
    "assets/textures/fire.png",
    "assets/textures/scissors.png",
    "assets/textures/human.png",
    "assets/textures/sponge.png",
    "assets/textures/paper.png",
    "assets/textures/air.png",
    "assets/textures/water.png",
    "assets/textures/gun.png",
    "assets/MonitoresPng/Alberto.png",
    "assets/MonitoresPng/Ana_Laura.png",
    "assets/MonitoresPng/Danilo.png",
    "assets/MonitoresPng/Felipe_santos.png",
    "assets/MonitoresPng/Felipe_Torres.png",
    "assets/MonitoresPng/Gabriel.png",
    "assets/MonitoresPng/Lucas.png",
    "assets/MonitoresPng/Matheus.png",
    "assets/Personagens/Player/Comeco.png"
};
static char soundsToLoad[TO_LOAD_SOUNDS][100] = {
    "assets/audios/door.wav",
    "assets/audios/death.wav",
    "sassets/audios/fire.wav",
    "assets/audios/scissors.wav",
    "assets/audios/paper.wav",
    "assets/audios/rock.wav",
    "assets/audios/gun.wav",
    "assets/audios/water.wav",
    "assets/audios/sponge.wav",
    "assets/audios/hit.wav",
    "assets/audios/air.wav"
};
static char musicsToLoad[TO_LOAD_MUSICS][100] = {
    "assets/musicas/Strength of the Titans.ogg",
    "assets/musicas/Gerudo Valley.ogg",
    "assets/musicas/The Edge of Green.ogg",
    "assets/musicas/At Doom's Gate.ogg",
    "assets/musicas/Find the Flame.ogg",
    "assets/musicas/To Sail Forbidden Seas.ogg",
    "assets/musicas/Final Game.ogg"
};
static char mapsToLoad[TO_LOAD_MAPS][100] = {
    "assets/tilemaps/map1.tmx",
    "assets/tilemaps/map2.tmx",
    "assets/tilemaps/map3.tmx",
    "assets/tilemaps/map4.tmx",
    "assets/tilemaps/map5.tmx",
    "assets/tilemaps/map6.tmx",
    "assets/tilemaps/map7.tmx",
    "assets/tilemaps/map8.tmx",
    "assets/tilemaps/map9.tmx",
    "assets/tilemaps/map10.tmx",
    "assets/tilemaps/map11.tmx"
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
    LoadSoundFile("assets/audios/sounds.txt");
}
void ToLoadMusics() {
    LoadMusicFile("assets/musicas/musics.txt");
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
