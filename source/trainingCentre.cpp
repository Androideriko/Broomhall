#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include "trainingCentre.h"

#include "army.h"
#include "farm.h"
#include "text.h"

void iniciateDataTrainingCentre(SDL_Renderer* renderer) {
    REDtrainingTexture = IMG_LoadTexture(renderer, "Assets/REDtraining.png");
    trainingIcon = IMG_LoadTexture(renderer, "Assets/trainingIcon.png");

    swordsmanIcon = IMG_LoadTexture(renderer, "Assets/swordsmanIcon.png");
    archerIcon = IMG_LoadTexture(renderer, "Assets/archerIcon.png");
    // spearmanIcon = IMG_LoadTexture(renderer, "Assets/spearmanIcon.png");
    
    trainingQueue.push_back({0, 0, 0, 0, 0});
    trainingQueue.push_back({0, 0, 0, 0, 0});
    trainingQueue.push_back({0, 0, 0, 0, 0});
    trainingQueueTimer.push_back(std::chrono::system_clock::now() + std::chrono::hours(72));
    trainingQueueTimer.push_back(std::chrono::system_clock::now() + std::chrono::hours(72));
    trainingQueueTimer.push_back(std::chrono::system_clock::now() + std::chrono::hours(72));

    std::srand(std::time(0));
}
void renderTrainingCentre(SDL_Renderer* renderer, int position, int inMenu) {
    SDL_Rect trainingButton = {100, 200, 50, 50};
    for (int i = 0; i < trainingCentre.size(); i++) {
        // Check if they are in picture
        if (trainingCentre[i].position - 1000 <= position and trainingCentre[i].position + 1000 >= position){
            SDL_Rect destRect = { trainingCentre[i].position - position, 455, 120, 100 };
            SDL_RenderCopy(renderer, REDtrainingTexture, nullptr, &destRect);
        }
    }
    for (int i = 0; i < trainingQueue.size(); i++) {
        if (std::chrono::system_clock::now() >= trainingQueueTimer[i] ) {
            for (int b = 0; b < trainingCentre.size(); b++) {
                if (trainingCentre[b].group == 0) {
                    addSoldier(renderer, trainingQueue[i][0], std::rand() % 21, 100);
                }
            }
            
            for (int a = 0; a < 4; a++) {
                trainingQueue[i][a] = trainingQueue[i][a + 1];
            }
            trainingQueue[i][4] = 0;
            if (trainingQueue[i][0] == 0) {
                trainingQueueTimer[i] = std::chrono::system_clock::now() + std::chrono::hours(72);
            } else {
                trainingQueueTimer[i] = std::chrono::system_clock::now() + std::chrono::seconds(5);
            }
        }
    }
    if (inMenu == 0 && trainingCentre.size()  > 0) {
        SDL_Rect destRect = { 90, 553, 45, 45 };
        SDL_RenderCopy(renderer, trainingIcon, nullptr, &destRect);
    }
}

void renderTrainingMenu(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 90, 60, 10, 255);
    SDL_Rect rect = {30, 30, 720, 550};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &boxSwordsman);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &boxArcher);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &boxSpearman);
    SDL_RenderCopy(renderer, swordsmanIcon, nullptr, &boxSwordsman);
    SDL_RenderCopy(renderer, archerIcon, nullptr, &boxArcher);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &box1);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &box2);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &box3);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &box4);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &box5);
    SDL_Rect destRect = { 230, 500, 30, 35};
    SDL_RenderCopy(renderer, breadIcon, nullptr, &destRect);
    TrainingText(renderer);
    for (int i = 0; i < 5; i++) {
        SDL_Rect box = {60 * (i + 1) - 10, 200, 50, 50};
        if (trainingQueue[0][i] == 1) {
            SDL_RenderCopy(renderer, swordsmanIcon, nullptr, &box);
        } else if (trainingQueue[0][i] == 2) {
            SDL_RenderCopy(renderer, archerIcon, nullptr, &box);
        }
        
    }
}

bool isOnTopTrainingCenter(SDL_Rect targetRect, int position) {
    for (int i = 0; i < trainingCentre.size(); i++) {
        SDL_Rect destRect = { trainingCentre[i].position - position, 405, 120, 100 };
        if (SDL_HasIntersection(&targetRect, &destRect)) {
            return false;        
        }
    }
    return true;
}

void addTrainingCenter(int type, int position) {
    trainingCentreStruct newTrainingCentre;
    newTrainingCentre.position = position;
    newTrainingCentre.health = 80;
    newTrainingCentre.group = type;
    trainingCentre.push_back(newTrainingCentre);
}
void actionTrainingCentre(SDL_Rect click) {
    if (SDL_HasIntersection(&click, &boxSwordsman)) {
        if (foodStorage[0] >= 8) {
            int i;
            for (i = 0; i < 5; i++) {
                if (trainingQueue[0][i] == 0) {
                    break;
                }
                
            }
            trainingQueue[0][i] = 1;
            if (i == 0) {
                trainingQueueTimer[0] = std::chrono::system_clock::now() + std::chrono::seconds(15);
            }
            foodStorage[0] -= 8;
        }
    } else if (SDL_HasIntersection(&click, &boxSpearman)) {
        if (foodStorage[0] >= 8) {
            int i;
            for (i = 0; i < 5; i++) {
                if (trainingQueue[0][i] == 0) {
                    break;
                }
            }
            if (i == 0) {
                trainingQueueTimer[0] = std::chrono::system_clock::now() + std::chrono::seconds(15);
            }
            trainingQueue[0][i] = 3;
            foodStorage[0] -= 8;
        }
    } else if (SDL_HasIntersection(&click, &boxArcher)) {
        if (foodStorage[0] >= 8) {
            int i;
            for (i = 0; i < 5; i++) {
                if (trainingQueue[0][i] == 0) {
                    break;
                }
            }
            if (i == 0) {
                trainingQueueTimer[0] = std::chrono::system_clock::now() + std::chrono::seconds(15);
            }
            trainingQueue[0][i] = 2;
            
            foodStorage[0] -= 8;
        }
    }
    
}
void startTrainingCentreMenu() {
    turnedOnTraining = true;
}
void endTrainingCentreMenu() {
    turnedOnTraining = false;
}