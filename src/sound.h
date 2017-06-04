#ifndef _SOUND_H
#define _SOUND_H

#include <Windows.h>
#include <SDL_mixer.h>

void loadingSounds();

void setSoundInit();

void setVolume(Mix_Chunk *chunk, float volume);

void playSound(int num);

#endif