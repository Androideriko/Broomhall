#include <SDL2/SDL_mixer.h>

#include "sounds.h"

void iniciateDataSounds() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        // Handle error
    }
    calmMusic = Mix_LoadMUS("Assets/backroundCalm.mp3");
    // Mix_Music* battleMusic = Mix_LoadMUS("Assets/battle.ogg");
    hammer = Mix_LoadWAV("Assets/hammer.mp3");
    footstep = Mix_LoadWAV("Assets/steps.wav");
    if (!footstep){
        // Handle error
    }
    Mix_VolumeChunk(footstep, MIX_MAX_VOLUME / 2);
}
void PlayFootstep() {
    Mix_PlayChannel(-1, footstep, 0);
}
void PlayHammer() {
    Mix_PlayChannel(-1, hammer, 0);
}
void PlayCalmMusic() {
    Mix_PlayMusic(calmMusic, -1);
}