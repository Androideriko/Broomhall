#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "nature.h"
#include "cityHall.h"
#include "army.h"
#include "buildMenu.h"
#include "farm.h"
#include "lumberMill.h"
#include "sounds.h"
#include "text.h"
#include "trainingCentre.h"


int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }
    
    // Initialize SDL_image for loading image files (PNG, JPG, etc.)
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_Quit();
        return 1;
    }
    
    // Create a window
    SDL_Window* window = SDL_CreateWindow("Broomhall", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
        
    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Inicialise the font
    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init: %s\n", TTF_GetError());
        // Handle error
    }
    TTF_Font* font = TTF_OpenFont("Assets/PixelatedFont.ttf", 24);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    
    // Main loop flag
    bool quit = false;
    SDL_Event e;
    
    int position = 0;
    int positionVelocity = 0;
    
    float sky[3] = {25.f, 25.f, 112.f};
    
    SDL_Rect buildButton = { 25, 553, 45, 45 };
    SDL_Rect trainingCentreButtonRect = { 90, 553, 45, 45 };
    SDL_Rect mouse;

    const int FPS = 200;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    
    int inMenu = 0;

    int mouseX;
    int mouseY;

    int selectBoxX = 0;
    int selectBoxY = 0;

    iniciateData(renderer);
    iniciateDataNature(renderer);
    iniciateDataArmy(renderer);
    iniciateDataBuildMenu(renderer);
    iniciateFarm(renderer);
    iniciateLumberMill(renderer);
    iniciateDataSounds();
    iniciateDataText(renderer);
    iniciateDataTrainingCentre(renderer);
    
    
    addCityHall(renderer, "RedCH.png", 100);
    addLumberMill(0, 260);
    addFarm(0, -30);
    addSoldier(renderer, 0, 200, 0);
    
    // Play backround music
    PlayCalmMusic();

    // Main loop
    while (!quit) {
        frameStart = SDL_GetTicks();
        // Handle events
        
        position += positionVelocity;
        
        // Clear the screen with a black color
        SDL_SetRenderDrawColor(renderer, (int) sky[0], (int) sky[1], (int) sky[2], 255); // RGB: black
        SDL_RenderClear(renderer);
        
        // Nature: update time and load ground
        updateTime(renderer, sky);
        loadGround(renderer, position);
        makeBirds(renderer);
        
        // Render and adjust all game objects
        renderCityHalls(renderer, position);
        renderFarms(renderer, position);
        renderLumberMills(renderer, position);
        
        foodUpdate(renderer);
        lumbermillUpdate(renderer);
        renderTrainingCentre(renderer, position, inMenu);
        
        renderArmy(renderer, position);
        
        renderBuildMenu(renderer, inMenu, position);

        
        if (inMenu == 1) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                mouseX = e.button.x;
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                    mouseY = e.button.y;
                    mouse = {mouseX, mouseY, 2, 2};
                    if (actionBuildMenu(renderer, mouse, -123, position)) {
                        inMenu = 0;
                    }
                }
                if (e.type == SDL_KEYDOWN or e.type == SDL_KEYUP) {
                    switch( e.type ){
                        case SDL_KEYDOWN:
                            switch( e.key.keysym.sym ){
                                case SDLK_a:
                                    positionVelocity = -1;
                                    break;
                                case SDLK_s:
                                    positionVelocity =  1;
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case SDL_KEYUP:
                            switch( e.key.keysym.sym ){
                                case SDLK_a:
                                    positionVelocity = 0;
                                    break;
                                case SDLK_s:
                                    positionVelocity =  0;
                                    break;
                                default:
                                    break;
                            }
                            break;
                    }
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        endBuildMenu();
                        inMenu = 0;
                    }
                }
                actionBuildMenu(renderer, mouse, mouseX, position);
            }
        }else if (inMenu == 2) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                    mouseX = e.button.x;
                    mouseY = e.button.y;
                    mouse = {mouseX, mouseY, 2, 2};
                    actionTrainingCentre(mouse);
                } else if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        endTrainingCentreMenu();
                        inMenu = 0;
                    }
                }
            }
            renderTrainingMenu(renderer);
        } else {
            if (selectBoxX != 0) {
                SDL_Rect rect = {selectBoxX, selectBoxY, mouseX - selectBoxX, mouseY - selectBoxY};
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
                SDL_RenderFillRect(renderer, &rect);                    
            }
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                mouseX = e.button.x;
                mouseY = e.button.y;
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                    mouse = {mouseX, mouseY, 2, 2};
                    if (SDL_HasIntersection(&mouse, &buildButton)) {
                        StartBuildMenu();
                        inMenu = 1;
                    } else if (SDL_HasIntersection(&mouse, &trainingCentreButtonRect)) {
                        startTrainingCentreMenu();
                        inMenu = 2;
                    } else {
                        selectBoxX = mouseX;
                        selectBoxY = mouseY;
                    }
                } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                    selectBoxX = mouseX;
                    selectBoxY = mouseY;
                } else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                    SDL_Keymod mods = SDL_GetModState();
                    if (abs(selectBoxX - mouseX) <= 5 && abs(selectBoxY - mouseY) <= 5) {
                        if (mods & KMOD_SHIFT) {
                            selectArmy(renderer, position, e.button.x, true);
                        } else {
                            selectArmy(renderer, position, e.button.x, false);
                        }
                    }else {
                        SDL_Rect rect = {selectBoxX, selectBoxY, mouseX - selectBoxX, mouseY - selectBoxY};
                        selectArmyBox(renderer, position, rect, false);
                    }
                    selectBoxX = 0;
                    selectBoxY = 0;
                } else {
                    switch( e.type ){
                        case SDL_KEYDOWN:
                            switch( e.key.keysym.sym ){
                                case SDLK_a:
                                    positionVelocity = -1;
                                    break;
                                case SDLK_s:
                                    positionVelocity =  1;
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case SDL_KEYUP:
                            switch( e.key.keysym.sym ){
                                case SDLK_a:
                                    positionVelocity = 0;
                                    break;
                                case SDLK_s:
                                    positionVelocity =  0;
                                    break;
                                default:
                                    break;
                            }
                            break;
                    }
                }
            }
        }

        // Present the rendered content
        SDL_RenderPresent(renderer);
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Clean up
    SDL_DestroyTexture(groundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}