// cityHall.h
#ifndef SOUNDS_h  // This is a guard to prevent multiple inclusions
#define SOUNDS_h

#include <SDL2/SDL_mixer.h>

static Mix_Chunk* footstep;
static Mix_Chunk* hammer;

static Mix_Music* calmMusic;

// Methods
void iniciateDataSounds();
void PlayFootstep();
void PlayCalmMusic();
void PlayHammer();

#endif