// buildMenu.h
#ifndef BUILDMENU_H
#define BUILDMENU_H

#include "farm.h"
#include "text.h"
#include "trainingCentre.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static SDL_Texture* buildIcon;
static SDL_Rect farmRect = { 40, 70, 45, 45 };
static SDL_Rect lumbermillRect = { 40, 130, 45, 45 };
static SDL_Rect trainingRect = { 40, 190, 45, 45 };

static bool turnedOn = false;
static int type = 0;
static int positionOnMap = 0;
static int canBuild = true;

void iniciateDataBuildMenu(SDL_Renderer* renderer);
void StartBuildMenu();
void endBuildMenu();
void renderBuildMenu(SDL_Renderer* renderer, int inMenu, int position);
bool actionBuildMenu(SDL_Renderer* renderer, SDL_Rect mouse, int position, int positionOnScreen);

#endif