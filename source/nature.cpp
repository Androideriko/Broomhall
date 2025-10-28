#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "nature.h"

SDL_Texture* Birds[2];

void iniciateDataNature(SDL_Renderer* renderer) {
    groundTexture = IMG_LoadTexture(renderer, "Assets/ground.png");
    sunTexture = IMG_LoadTexture(renderer, "Assets/sun.png");
    backroundTexture = IMG_LoadTexture(renderer, "Assets/backround.png");
    Birds[0] = IMG_LoadTexture(renderer, "Assets/Birds1.png");
    Birds[1] = IMG_LoadTexture(renderer, "Assets/Birds2.png");
    if (groundTexture == nullptr) {
        printf("Error: could not load game data.\n");
    }
}

void updateTime(SDL_Renderer* renderer, float now[3]) {
    static bool increasing = false;
    static int counter = 0;
    if (now[0] < 30) {
        increasing = true;
    }
    if (now[0] > 80) {
        increasing = false;
    }
    SDL_Rect destRect = { 10, 30, 50, 50 };
    if (counter == 300) {
        if (!increasing) {
            now[0] -= 1.f;
            now[1] -= 1.f;
            now[2] -= 1.f;
            destRect = { 10, 30, 50, 50 };
        } else {
            now[0] += 1.f;
            now[1] += 1.f;
            now[2] += 1.f;
        }
        counter = 0;
    }
    counter++;
    SDL_RenderCopy(renderer, sunTexture, nullptr, &destRect);
    // Render the ground texture
}
void makeBirds(SDL_Renderer* renderer) {
    static bool fliing = false;
    static int xBirds = -30;
    static int frame = 0;
    static int cooldown = 0;
    static int randomNumber;
    if (fliing) {
        xBirds++;
        SDL_Rect destRect = { xBirds, 100 + randomNumber, 50, 50 };
        SDL_RenderCopy(renderer, Birds[frame], nullptr, &destRect);
        if (cooldown >= 100) {
            if (frame == 0) {
                frame = 1;
            } else {
                frame = 0;
            }
            cooldown = 0;
        }
        cooldown++;
        if (xBirds > 1000) {
            fliing = false;
        }
    } else {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        randomNumber = std::rand() % 1000;
        if (randomNumber <= 30) {
            fliing = true;
            xBirds = -30;
        }
    }
    
    
}

void loadGround(SDL_Renderer* renderer, int position) {
    int calc = position % 50;
    SDL_Rect destRect = { 0, 00, 800, 600 };
    SDL_RenderCopy(renderer, backroundTexture, nullptr, &destRect);
    for (int x = calc * -1 - 50; x < calc + 1000; x+=50) {
        SDL_Rect destRect = { x, 550, 50, 50 };
        SDL_RenderCopy(renderer, groundTexture, nullptr, &destRect);
    }
}