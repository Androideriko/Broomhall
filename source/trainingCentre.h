// trainingCentre.h
#ifndef TRAININGCENTRE_H
#define TRAININGCENTRE_H

#include "farm.h"
#include "text.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <vector>
#include <array>
#include <chrono>
#include <cstdlib>
#include <ctime>

static SDL_Texture* REDtrainingTexture;
static SDL_Texture* trainingIcon;

static SDL_Texture* swordsmanIcon;
static SDL_Texture* archerIcon;
static SDL_Texture* spearmanIcon;

static SDL_Rect boxSwordsman = {50, 500, 50, 50};
static SDL_Rect boxArcher = {110, 500, 50, 50};
static SDL_Rect boxSpearman = {170, 500, 50, 50};

static SDL_Rect box1 = {50, 200, 50, 50};
static SDL_Rect box2 = {110, 200, 50, 50};
static SDL_Rect box3 = {170, 200, 50, 50};
static SDL_Rect box4 = {230, 200, 50, 50};
static SDL_Rect box5 = {290, 200, 50, 50};

static bool turnedOnTraining = false;
static int trainingType = 0;

struct trainingCentreStruct {
    int position;
    int health;
    int group;
};
static std::vector<trainingCentreStruct> trainingCentre;
static std::vector<std::array<int, 5>> trainingQueue;
static std::vector<std::chrono::system_clock::time_point> trainingQueueTimer;

void iniciateDataTrainingCentre(SDL_Renderer* renderer);
bool isOnTopTrainingCenter(SDL_Rect targetRect, int position);
void renderTrainingCentre(SDL_Renderer* renderer, int position, int inMenu);
void renderTrainingMenu(SDL_Renderer* renderer);
void addTrainingCenter(int type, int position);
void actionTrainingCentre(SDL_Rect click);
void startTrainingCentreMenu();
void endTrainingCentreMenu();

#endif