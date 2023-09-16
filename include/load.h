#ifndef LOAD_H
#define LOAD_H
#include "raylib.h"
#include <tmx.h>

tmx_map* GetMap(int map); // return the map using the map index, return NULL if not found
Texture* GetTexture(int texture); // return idx using name, return -1 if not found

void LoadConfig(); // get config file and save in a struct
void SaveConfig(); // save config file

void LoadTexts(); // get text files and save in a vector of texts
void M_LoadTexture(); // get texture file and saves in dynamic array of textures
void M_LoadMap(); // get map file and saves in dynamic array of maps

void ToLoadTextures(); // get texture files and saves in vector of textures
void ToLoadSounds(); // get sound files and saves in vector of sounds
void ToLoadMusics(); // get music files and saves in vector of musics

int SaveGame(); // save game in a file, return 1 if success and 0 if not
int LoadGame(); // load game from a file, return 1 if success and 0 if not

float UpdateLoadAll();  // load all textures, sounds and musics and return loadProgress 
                        // -> 0.0f to 1.0f
                        // -> -1.0f if error
char* LoadingStatus(); // return a string with the current loading status
void UnloadResources(); // unload all textures, sounds and musics and free memory


#endif