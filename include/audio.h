#ifndef AUDIO_H
#define AUDIO_H

// declaracao das funcoes --------------------------
int MusicTest(); // aux function
void StartMusic(); // start playing a music that could be identified by a config file
void ChangeMusic(int musicIdx); // change music to another one
void PauseMusic(); // pauses music

void UpdateMusic();
void PlaySoundIdx(int soundIdx); // play a sound that could be identified by a index
// to change the master volume, use SetMasterVolume(float volume)
void ChangeMusicVolume(float volume); // change all musics volume
void ChangeSoundEffectVolume(float volume); // change all sound effects volume
void ResumeMusic(int musicIDX); // resume a paused music
void LoadSoundFile(const char *fileName); // load sound and save in dynamic array of sounds
void LoadMusicFile(const char *fileName); // load music and save in dynamic array of musics

void UnloadAll_Audio(); // unload all sounds and musics and free memory
// ---------------------------------------------------
#endif
