// cityHall.h
#ifndef TEXT_h  // This is a guard to prevent multiple inclusions
#define TEXT_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

static TTF_Font* font;
static SDL_Texture* breadAmount;
static SDL_Texture* woodAmount;
static SDL_Rect breadDestRect;
static SDL_Color color;

static SDL_Surface* title;
static SDL_Surface* buildFarm;
static SDL_Surface* buildLumbermill;
static SDL_Surface* buildTraining;
static SDL_Surface* trainingCentreTitle;
static SDL_Surface* trainingBreadCost;
static SDL_Texture* titleTexture;
static SDL_Texture* buildFarmTexture;
static SDL_Texture* lumbermillTexture;
static SDL_Texture* trainingTexture;
static SDL_Texture* trainingCentreTitleTexture;
static SDL_Texture* trainingBreadCostTexture;

// Methods
void iniciateDataText(SDL_Renderer* renderer);
void foodUpdate(SDL_Renderer* renderer);
void lumbermillUpdate(SDL_Renderer* renderer);
void BuildMenuText(SDL_Renderer* renderer);
void TrainingText(SDL_Renderer* renderer);

#endif