// lumberMill.h
#ifndef LUMBERMILL_H
#define LUMBERMILL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <chrono>

static SDL_Texture* REDlumberMill;
static SDL_Texture* woodIcon;

struct millStruct {
    int position;
    int health;
    std::chrono::system_clock::time_point timeToAdd;
    SDL_Texture* texture;
    int group;
};
static std::vector<millStruct> LumberMills;
extern std::vector<int> woodStorage;

void iniciateLumberMill(SDL_Renderer* renderer);
bool isOnTopLumberMill(SDL_Rect targetRect, int position);
void addLumberMill(int color, int position);
void renderLumberMills(SDL_Renderer* renderer, int position);

#endif