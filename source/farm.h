// buildMenu.h
#ifndef FARM_H
#define FARM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <chrono>

static SDL_Texture* REDfarm;
extern SDL_Texture* breadIcon;

struct farmStruct {
    int position;
    int health;
    std::chrono::system_clock::time_point timeToAdd;
    SDL_Texture* texture;
    int group;
};
static std::vector<farmStruct> Farms;
extern std::vector<int> foodStorage;

void iniciateFarm(SDL_Renderer* renderer);
bool isOnTopFarm(SDL_Rect targetRect, int position);
void addFarm(int color, int position);
void renderFarms(SDL_Renderer* renderer, int position);

#endif