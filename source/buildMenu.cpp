#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <vector>

#include "buildMenu.h"
#include "cityHall.h"
#include "farm.h"
#include "text.h"
#include "sounds.h"
#include "trainingCentre.h"
#include "lumberMill.h"

void iniciateDataBuildMenu(SDL_Renderer* renderer) {
    buildIcon = IMG_LoadTexture(renderer, "Assets/buildicon.png");
}

void StartBuildMenu() {
    turnedOn = true;
}
void endBuildMenu() {
    turnedOn = false;
    type = 0;
}
void renderBuildMenu(SDL_Renderer* renderer, int inMenu, int position) {
    if (type == 0) {
        if (turnedOn) {
            SDL_SetRenderDrawColor(renderer, 90, 60, 10, 255);
            SDL_Rect rect = {30, 30, 720, 550};
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &farmRect);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &lumbermillRect);
            BuildMenuText(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &trainingRect);
            BuildMenuText(renderer);
        }else {
            if (inMenu == 0) {
                SDL_Rect destRect = { 25, 553, 45, 45 };
                SDL_RenderCopy(renderer, buildIcon, nullptr, &destRect);
            }
        }
    } else {
        SDL_Rect rect = {positionOnMap, 455, 120, 100};
        if (isOnTopCityHall(rect, position) && isOnTopTrainingCenter(rect, position) && isOnTopFarm(rect, position) && isOnTopLumberMill(rect, position)) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
            canBuild = true;
        }else {
            SDL_SetRenderDrawColor(renderer, 200, 81, 42, 100);
            canBuild = false;
        }
        SDL_RenderFillRect(renderer, &rect);
    }
    
}

bool actionBuildMenu(SDL_Renderer* renderer, SDL_Rect mouse, int position, int positionOnScreen) {
    if (position != -123) {
        positionOnMap = position - 60;
        return false;
    }
    if (type == 0) {
        if (SDL_HasIntersection(&mouse, &farmRect)) {
            type = 1;
        }else if (SDL_HasIntersection(&mouse, &lumbermillRect)) {
            type = 2;
        }else if (SDL_HasIntersection(&mouse, &trainingRect)) {
            type = 3;
        }
    } else {
        if (!canBuild) {
            return false;
        }
        if (type == 1) {
            addFarm(0, positionOnMap + positionOnScreen);
        } else if (type == 2) {
            addLumberMill(0,  positionOnMap + positionOnScreen);
        } else if (type == 3) {
            addTrainingCenter(0,  positionOnMap + positionOnScreen);
        }
        PlayHammer();
        type = 0;
        turnedOn = false;
        printf("%d\n", type);
        return true;
    }
    return false;
}