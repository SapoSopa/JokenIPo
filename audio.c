#include "include/audio.h"

#include "stdlib.h"
#include "raylib.h"

typedef struct {
    char name[100];
    Sound sound;
} NameSound;

typedef struct {
    char name[100];
    Music music;
} NameMusic;

static NameSound *sounds = NULL;
static NameMusic *musics = NULL;

static int soundsLen = 0;
static int musicsLen = 0;

char** GetMusics(int *len) {
}

void StartMusic() {
}
void ChangeMusic(int musicIdx) {
}
void PauseMusic() {
}

void PlaySoundIdx(int soundIdx){
}

int LoadSoundFile(const char *fileName) {
}
int LoadMusicFile(const char *fileName) {
}

void UnloadAll_Audio() {
}
