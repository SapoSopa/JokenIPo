#ifndef AUDIO_H
#define AUDIO_H

// musicas ------------------------------------
const int mainmusicIDX = 0;
const int secondmusicIDX = 1;
const int map1IDX = 2;
const int map2IDX = 3;
const int map3IDX = 4;
const int map4IDX = 5;
const int map5IDX = 6;
const int map6IDX = 7;
const int map7IDX = 8;
const int map8IDX = 9;
const int map9IDX = 10;
const int map10IDX = 11;
const int map11IDX = 12;
const int endmusicIDX = 13;
// ------------------------------------------------

// sounds --------------------------------------
const int hitIDX = 0;
const int walkIDX = 1;
const int doorIDX = 2;
const int deathIDX = 3;
const int fireIDX = 4;
const int scissorsIDX = 5;
const int paperIDX = 6;
const int rockIDX = 7;
const int gunIDX = 8;
const int waterIDX = 9;
const int spongeIDX = 10;
const int humanIDX = 11;
const int airIDX = 12;
// -------------------------------------------------

// declaracao das funcoes --------------------------
void StartMusic(); // start playing a music that could be identified by a config file
void ChangeMusic(int musicIdx); // change music to another one
void PauseMusic(); // pauses music

void PlaySoundIdx(int soundIdx); // play a sound that could be identified by a index
void ChangeMusicVolume(float volume, int musicIdx); // change the music volume
int LoadSoundFile(const char *fileName); // load sound and save in dynamic array of sounds
int LoadMusicFile(const char *fileName); // load music and save in dynamic array of musics

void UnloadAll_Audio(); // unload all sounds and musics and free memory
// ---------------------------------------------------
#endif
