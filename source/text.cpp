#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "text.h"
#include "farm.h"
#include "lumberMill.h"

void iniciateDataText(SDL_Renderer* renderer) {
    font = TTF_OpenFont("Assets/PixelatedFont.ttf", 24);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }
    color = {0, 0, 0};
    title = TTF_RenderText_Solid(font,  "Build Menu", color);
    buildFarm = TTF_RenderText_Solid(font,  "Build Farm", color);
    buildLumbermill = TTF_RenderText_Solid(font,  "Build Lumber Mill", color);
    buildTraining = TTF_RenderText_Solid(font,  "Build Training Centre", color);
    trainingCentreTitle = TTF_RenderText_Solid(font,  "Training Center Menu", color);
    trainingBreadCost = TTF_RenderText_Solid(font,  "8", color);
    titleTexture = SDL_CreateTextureFromSurface(renderer, title);
    trainingBreadCostTexture = SDL_CreateTextureFromSurface(renderer, trainingBreadCost);
    trainingCentreTitleTexture = SDL_CreateTextureFromSurface(renderer, trainingCentreTitle);
    buildFarmTexture = SDL_CreateTextureFromSurface(renderer, buildFarm);
    lumbermillTexture = SDL_CreateTextureFromSurface(renderer, buildLumbermill);
    trainingTexture = SDL_CreateTextureFromSurface(renderer, buildTraining);
}

void foodUpdate(SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Solid(font,  std::to_string(foodStorage[0]).c_str(), color);
    breadAmount = SDL_CreateTextureFromSurface(renderer, surface);
    breadDestRect = {60, 70, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, breadAmount, NULL, &breadDestRect);  
}
void lumbermillUpdate(SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Solid(font,  std::to_string(woodStorage[0]).c_str(), color);
    woodAmount = SDL_CreateTextureFromSurface(renderer, surface);
    breadDestRect = {60, 120, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, woodAmount, NULL, &breadDestRect);
}

void TrainingText(SDL_Renderer* renderer) {
    SDL_Rect destRect = {40, 40, trainingCentreTitle->w, trainingCentreTitle->h};
    SDL_RenderCopy(renderer, trainingCentreTitleTexture, NULL, &destRect);
    destRect = {265, 510, trainingBreadCost->w, trainingBreadCost->h};
    SDL_RenderCopy(renderer, trainingBreadCostTexture, NULL, &destRect);
}

void BuildMenuText(SDL_Renderer* renderer) {
    SDL_Rect titleRect = {40, 40, title->w, title->h};
    SDL_Rect farmRect = {100, 80, buildFarm->w, buildFarm->h};
    SDL_Rect lumbermillRect = {100, 140, buildLumbermill->w, buildLumbermill->h};
    SDL_Rect trainingRect = {100, 200, buildTraining->w, buildTraining->h};
    breadAmount = SDL_CreateTextureFromSurface(renderer, buildTraining);
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);  
    SDL_RenderCopy(renderer, buildFarmTexture, NULL, &farmRect);
    SDL_RenderCopy(renderer, lumbermillTexture, NULL, &lumbermillRect);  
    SDL_RenderCopy(renderer, trainingTexture, NULL, &trainingRect);  
}