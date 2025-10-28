// nature.h
#ifndef NATURE_H  // This is a guard to prevent multiple inclusions
#define NATURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>

static SDL_Texture* groundTexture;
static SDL_Texture* sunTexture;
static SDL_Texture* backroundTexture;

extern SDL_Texture* Birds[2];

// Function declarations
void iniciateDataNature(SDL_Renderer* renderer); // Loads all data needed(images)
void updateTime(SDL_Renderer* renderer, float now[3]);  // A function to update the time
void loadGround(SDL_Renderer* renderer, int positions);  // Loads ground
void makeBirds(SDL_Renderer* renderer); // Generates and makes birds move

#endif  // End of guard