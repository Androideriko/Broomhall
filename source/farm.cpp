#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <vector>
#include <chrono>

#include "farm.h"

std::vector<int> foodStorage;
SDL_Texture* breadIcon = nullptr;

void iniciateFarm(SDL_Renderer* renderer) {
    REDfarm = IMG_LoadTexture(renderer, "Assets/REDfarm.png");
    breadIcon = IMG_LoadTexture(renderer, "Assets/breadicon.png");
    foodStorage.push_back(0);
    foodStorage.push_back(0);
    foodStorage.push_back(0);
}
void addFarm(int color, int position) {
    farmStruct tempFarm;
    tempFarm.health = 60;
    tempFarm.position = position;
    tempFarm.group = color;
    tempFarm.timeToAdd = std::chrono::system_clock::now() + std::chrono::seconds(3);
    if (color == 0) {
        tempFarm.texture = REDfarm;
    }
    Farms.push_back(tempFarm);
}
void renderFarms(SDL_Renderer* renderer, int position) {
    SDL_Rect destRect = { 20, 65, 30, 35};
    SDL_RenderCopy(renderer, breadIcon, nullptr, &destRect);
    for (int i = 0; i < Farms.size(); i++) {
        // Check if they are in picture
        if (Farms[i].position - 1000 <= position and Farms[i].position + 1000 >= position){
            SDL_Rect destRect = { Farms[i].position - position, 455, 120, 100 };
            SDL_RenderCopy(renderer, Farms[i].texture, nullptr, &destRect);
        }
        if (std::chrono::system_clock::now() >= Farms[i].timeToAdd ) {
            Farms[i].timeToAdd = std::chrono::system_clock::now() + std::chrono::seconds(3);
            foodStorage[Farms[i].group] += 1;
        }
    }
}

bool isOnTopFarm(SDL_Rect targetRect, int position) {
    for (int i = 0; i < Farms.size(); i++) {
        SDL_Rect destRect = { Farms[i].position - position, 405, 120, 100 };
        if (SDL_HasIntersection(&targetRect, &destRect)) {
            return false;        
        }
    }
    return true;
}