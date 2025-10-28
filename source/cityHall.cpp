#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>

#include "cityHall.h"

std::vector<cityHallsStruct> CityHalls;

void iniciateData(SDL_Renderer* renderer){
    iconCH = IMG_LoadTexture(renderer, "Assets/iconCH.png");
    if (iconCH== nullptr) {
        printf("Error: could not load game data.\n");
    }
}

void renderCityHalls(SDL_Renderer* renderer, int position){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = {15, 15, 125, 150};
    SDL_RenderFillRect(renderer, &rect);

    // City Hall icon and health bar
    SDL_Rect destRect = { 20, 20, 35, 35};
    SDL_RenderCopy(renderer, iconCH, nullptr, &destRect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    rect = {65, 35, 55, 15};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    rect = {65, 35, (int)floor(CityHalls[0].health*0.158), 15};
    SDL_RenderFillRect(renderer, &rect);
    
    // Render city halls
    for (int i = 0; i < CityHalls.size(); i++) {
        // Check if they are in picture
        if (CityHalls[i].position - 1000 <= position and CityHalls[i].position + 1000 >= position){
            SDL_Rect destRect = { CityHalls[i].position - position, 405, 150, 150 };
            SDL_RenderCopy(renderer, CityHalls[i].texture, nullptr, &destRect);
        }
    }
}

bool isOnTopCityHall(SDL_Rect targetRect, int position) {
    for (int i = 0; i < CityHalls.size(); i++) {
        SDL_Rect destRect = { CityHalls[i].position - position, 405, 150, 150 };
        if (SDL_HasIntersection(&targetRect, &destRect)) {
            return false;        
        }
    }
    return true;
}

void addCityHall(SDL_Renderer* renderer, std::string color, int position) {
    cityHallsStruct newCityHall;
    newCityHall.position = position;
    newCityHall.health = 350;
    color = "Assets/" + color;
    newCityHall.texture = IMG_LoadTexture(renderer, color.c_str());
    CityHalls.push_back(newCityHall);
}