#include "include/audio.h"
#include "include/resourcesIdx.h"

#include "stdio.h"

#include "raylib.h"

typedef struct {
    char name[100];
    Sound sound;
} NameSound;

typedef struct {
    char name[100];
    Music music;
} NameMusic;

static NameSound sounds[11];
static NameMusic musics[7]; // definindo o tamanho ainda

static int soundsLen = 0;
static int musicsLen = 0;

int MusicTest(){
    bool flag = false, index = -1;
    for(int i = 0; i < musicsLen && !flag; i++){
        if(IsMusicStreamPlaying(musics[i].music)){
            index = i;
            flag = true;
        }
    }
    return index;
}

void StartMusic() {
    SetMasterVolume(0.30);
    PlayMusicStream(musics[music_main].music);// começa tocando a primeira musica, no caso, a principal
    musics[music_main].music.looping = true; // starta o loop
    UpdateMusicStream(musics[music_main].music);
}
void ChangeMusic(int musicIdx) {
    int index = MusicTest();
    if(index != -1)
        StopMusicStream(musics[index].music);
    PlayMusicStream(musics[musicIdx].music);
    musics[musicIdx].music.looping = true;
}

void PauseMusic() {
    int index = MusicTest();
    if(index != -1)
        PauseMusicStream(musics[index].music);
}

void UpdateMusic(){
    int index = MusicTest();
    if(index != -1)
        UpdateMusicStream(musics[index].music);
}
// função pra resumir
void ResumeMusic(int musicIDX){
    if (!IsMusicStreamPlaying(musics[musicIDX].music))
        ResumeMusicStream(musics[musicIDX].music);
}
// criei uma função para mudar o volume da musica.
void ChangeMusicVolume(float volume){
    for(int i = 0; i < musicsLen; i++){
        SetMusicVolume(musics[i].music, volume);
    }
}

void ChangeSoundEffectVolume(float volume){
    for(int i = 0; i < soundsLen; i++){
        SetSoundVolume(sounds[i].sound, volume);
    }
}

void PlaySoundIdx(int soundIdx){
    PlaySound(sounds[soundIdx].sound);
}

void LoadSoundFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    char audios[11][100] = {
        "assets/audios/door.mp3",
        "assets/audios/death.mp3",
        "sassets/audios/fire.mp3",
        "assets/audios/scissors.mp3",
        "assets/audios/paper.mp3",
        "assets/audios/rock.mp3",
        "assets/audios/gun.mp3",
        "assets/audios/water.mp3",
        "assets/audios/sponge.mp3",
        "assets/audios/hit.mp3",
        "assets/audios/air.mp3"
    };
    while(!feof(file)){
        fscanf(file, " %99[^\n]", sounds[soundsLen].name);
        sounds[soundsLen].sound = LoadSound(audios[soundsLen]);
        soundsLen++; 
    }
    for(int i = 0; i < soundsLen; i++)
        SetSoundVolume(sounds[i].sound, 0.10);
    fclose(file);
}

// incompleto
void LoadMusicFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    char songs[6][100] = {
        "assets/musicas/Strength of the Titans.mp3",
        "assets/musicas/Gerudo Valley.mp3",
        "assets/musicas/The Edge of Green.mp3",
        "assets/musicas/At Doom's Gate.mp3",
        "assets/musicas/Find the Flame.mp3",
        "assets/musicas/To Sail Forbidden Seas.mp3"
    // falta adicionar a musica final
    };
    while(!feof(file)){
        fscanf(file, " %99[^\n]", musics[musicsLen].name);
        musics[musicsLen].music = LoadMusicStream(songs[musicsLen]);
        musicsLen++; 
    }
    for(int i = 0; i < musicsLen; i++)
        SetMusicVolume(musics[i].music, 0.20);
    fclose(file);
}

void UnloadAll_Audio() {
    for(int i = 0; i < musicsLen;i++)
        UnloadMusicStream(musics[i].music);
    
     for(int i = 0; i < soundsLen;i++)
        UnloadSound(sounds[i].sound);
    
    CloseAudioDevice();
}


