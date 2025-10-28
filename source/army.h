// army.h
#ifndef ARMY_H  // This is a guard to prevent multiple inclusions
#define ARMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <ctime>

struct armyStruct {
    int ID;
    int position;
    int health;
    int type;
    int target;
    bool shift;
    SDL_RendererFlip facing;
    int color;
    int cooldown;
    int frame;
    bool selected;
};
extern std::vector<armyStruct> Army;
extern SDL_Texture* REDswordsman[6];
static std::vector<int> selected;

// Function declarations
void iniciateDataArmy(SDL_Renderer* renderer);
void addSoldier(SDL_Renderer* renderer, int type, int position, int color);
void renderArmy(SDL_Renderer* renderer, int position);
void selectArmyBox(SDL_Renderer* renderer, int position, SDL_Rect box, bool shift);
void selectArmy(SDL_Renderer* renderer, int position, int click, bool shift);

#endif  // End of guard