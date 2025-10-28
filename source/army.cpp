#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <vector>
#include <ctime>

#include "army.h"
#include "farm.h"
#include "sounds.h"

std::vector<armyStruct> Army;
SDL_Texture* REDswordsman[6];

void iniciateDataArmy(SDL_Renderer* renderer){
    REDswordsman[0] = IMG_LoadTexture(renderer, "Assets/REDswordsman1.png");
    REDswordsman[1] = IMG_LoadTexture(renderer, "Assets/REDswordsman2.png");
    REDswordsman[2] = IMG_LoadTexture(renderer, "Assets/REDswordsman3.png");
    REDswordsman[3] = IMG_LoadTexture(renderer, "Assets/REDswordsman4.png");
    REDswordsman[4] = IMG_LoadTexture(renderer, "Assets/REDswordsman5.png");
    REDswordsman[5] = IMG_LoadTexture(renderer, "Assets/REDswordsman6.png");
}
void addSoldier(SDL_Renderer* renderer, int type, int position, int color) {
    armyStruct newArmy;
    newArmy.position = position;
    newArmy.health = 100;
    newArmy.type = type;
    newArmy.color = color;
    newArmy.cooldown = 0;
    newArmy.frame = 0;
    newArmy.target = position;
    newArmy.facing = SDL_FLIP_NONE;
    newArmy.shift = false;
    newArmy.selected = false;
    Army.push_back(newArmy);
}
void renderArmy(SDL_Renderer* renderer, int position) {
    for (int i = 0; i < Army.size(); i++) {
        // Move Soldier torwards target
        int calc = Army[i].target - Army[i].position;
        if (calc > 0){
            Army[i].position++;
            Army[i].facing = SDL_FLIP_NONE;
        }else if (calc < 0) {
            Army[i].position--;
            Army[i].facing = SDL_FLIP_HORIZONTAL;
        }else if (Army[i].frame != 0 and Army[i].frame != 1) {
            Army[i].frame = 0;
        }
        // Check if they are in picture
        if (Army[i].position - 1000 <= position and Army[i].position + 1000 >= position){
            if (Army[i].cooldown >= 100) {
                if (Army[i].frame == 0) {
                    Army[i].frame = 1;
                }else if (Army[i].frame == 1) {
                    Army[i].frame = 0;
                }
                else if (Army[i].frame == 2) {
                    Army[i].frame = 3;
                    PlayFootstep();
                    
                }
                else if (Army[i].frame == 3) {
                    Army[i].frame = 2;
                    PlayFootstep();
                }
                else if (Army[i].frame == 4) {
                    Army[i].frame = 5;
                }
                else {
                    Army[i].frame = 5;
                }
                Army[i].cooldown = 0;
            }
            Army[i].cooldown++;
            SDL_Rect destRect = { Army[i].position - position, 513, 40, 40 };
            SDL_RenderCopyEx(renderer, REDswordsman[Army[i].frame], nullptr, &destRect, 0.0, nullptr, Army[i].facing);
            if (Army[i].selected) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
                SDL_Rect rect = {Army[i].position - position, 513, 40, 40};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void selectArmyBox(SDL_Renderer* renderer, int position, SDL_Rect box, bool shift) {
    if (selected.size() == 0) {
        for (int i = Army.size() - 1; i > -1; i--) {
            SDL_Rect targetSoldier = { Army[i].position - position, 513, 40, 40 };
            if (SDL_HasIntersection(&box, &targetSoldier)) {
                selected.push_back(i);
                Army[i].selected = true;
            }
        }
    }
}

void selectArmy(SDL_Renderer* renderer, int position, int click, bool shift) {
    int onMapClick = position + click;
    if (selected.size() == 0) {
        for (int i = Army.size() - 1; i > -1; i--) {
            if (onMapClick >= Army[i].position and onMapClick <= Army[i].position + 40) {
                selected.push_back(i);
                Army[i].selected = true;
                break;
            }
        }
    } else {
        for (int number : selected) {
            Army[number].target = click + position - 20 + (std::rand() % 41) - 20;
            Army[number].frame = 3;
            Army[number].selected = false;
        }
        selected.clear();
    }
}