#include "include/audio.h"
#include "include/resourcesIdx.h"

#include "string.h"
#include "stdio.h"
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

void StartMusic() {
    SetMasterVolume(0.20);
    PlayMusicStream(musics[music_main].music);// começa tocando a primeira musica, no caso, a principal
    musics[music_main].music.looping = true; // starta o loop
    UpdateMusicStream(musics[music_main]);
}
void ChangeMusic(int musicIdx) {
    bool flag = false, index;
    for(int i = 0; i < musicsLen && !flag; i++){
        if(IsMusicStreamPlaying(musics[i].music)){
            flag = true;
            index = i;
        }
    }
    StopMusicStream(musics[index].music);
    PlayMusicStream(musics[musicIdx].music);
    musics[musicIdx].music.looping = true;
}

void PauseMusic() {
    bool flag = false, index;
    for(int i = 0; i < musicsLen && !flag; i++){
        if(IsMusicStreamPlaying(musics[i].music)){
            flag = true;
            index = i;
        }
    }
    PauseMusicStream(musics[index].music);
}

// função pra resumir
void ResumeMusic(int musicIDX){
    ResumeMusicStream(musics[i].music);
}
// criei uma função para mudar o volume da musica.
void ChangeMusicVolume(float volume, int musicIdx){
    SetMusicVolume(musics[musicIdx].music, volume);
}

void PlaySoundIdx(int soundIdx){
    PlaySound(sounds[soundIdx].sound);
}

void LoadSoundFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    while(!feof(file)){
        sounds = (NameSound *) realloc(sounds, (soundsLen+1) * sizeof(NameSound));
        fscanf(file, " %99[^\n]", sounds[soundsLen].name);
        char aux[100] = "assets/audios/";
        strcat(aux, sounds[soundsLen].name);
        sounds[soundsLen].sound = LoadSound(aux);
        soundsLen++; 
    }
    fclose(file);
}
void LoadMusicFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    while(!feof(file)){
        musics = (NameMusic *) realloc(musics, (musicsLen+1) * sizeof(NameMusic));
        fscanf(file, " %99[^\n]", musics[musicsLen].name);
        char aux[100] = "assets/audios/";
        strcat(aux, musics[musicsLen].name);
        musics[musicsLen].music = LoadMusicStream(aux);
        musicsLen++; 
    }
    fclose(file);
}

void UnloadAll_Audio() {
    for(int i = 0; i < musicsLen;i++)
        UnloadMusicStream(musics[i].music);
    
     for(int i = 0; i < soundsLen;i++)
        UnloadSound(sounds[i].sound);
    
    free(musics);
    free(sounds);
    CloseAudioDevice();
}

