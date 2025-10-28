// cityHall.h
#ifndef CITYHALL_h  // This is a guard to prevent multiple inclusions
#define CITYHALL_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>

// Attributes
struct cityHallsStruct {
    int position;
    int health;
    SDL_Texture* texture;
};
extern std::vector<cityHallsStruct> CityHalls;
static SDL_Texture* iconCH;
// Methods
void iniciateData(SDL_Renderer* renderer);
bool isOnTopCityHall(SDL_Rect targetRect, int position);
void renderCityHalls(SDL_Renderer* renderer, int position);
void addCityHall(SDL_Renderer* renderer, std::string color, int position);

#endif