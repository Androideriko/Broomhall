#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <vector>
#include <chrono>

#include "lumberMill.h"

std::vector<int> woodStorage;

void iniciateLumberMill(SDL_Renderer* renderer) {
    REDlumberMill = IMG_LoadTexture(renderer, "Assets/REDlumbermill.png");
    woodIcon = IMG_LoadTexture(renderer, "Assets/logicon.png");
    woodStorage.push_back(0);
    woodStorage.push_back(0);
    woodStorage.push_back(0);
}
void addLumberMill(int color, int position) {
    millStruct tempFarm;
    tempFarm.health = 60;
    tempFarm.position = position;
    tempFarm.group = color;
    tempFarm.timeToAdd = std::chrono::system_clock::now() + std::chrono::seconds(3);
    if (color == 0) {
        tempFarm.texture = REDlumberMill;
    }
    LumberMills.push_back(tempFarm);
}
void renderLumberMills(SDL_Renderer* renderer, int position) {
    SDL_Rect destRect = { 20, 105, 35, 35};
    SDL_RenderCopy(renderer, woodIcon, nullptr, &destRect);
    for (int i = 0; i < LumberMills.size(); i++) {
        // Check if they are in picture
        if (LumberMills[i].position - 1000 <= position and LumberMills[i].position + 1000 >= position){
            SDL_Rect destRect = { LumberMills[i].position - position, 455, 120, 100 };
            SDL_RenderCopy(renderer, LumberMills[i].texture, nullptr, &destRect);
        }
        if (std::chrono::system_clock::now() >= LumberMills[i].timeToAdd ) {
            LumberMills[i].timeToAdd = std::chrono::system_clock::now() + std::chrono::seconds(3);
            woodStorage[LumberMills[i].group] += 1;
        }
    }
}

bool isOnTopLumberMill(SDL_Rect targetRect, int position) {
    for (int i = 0; i < LumberMills.size(); i++) {
        SDL_Rect destRect = { LumberMills[i].position - position, 405, 120, 100 };
        if (SDL_HasIntersection(&targetRect, &destRect)) {
            return false;        
        }
    }
    return true;
}