#include <iostream>
#include "./Constants.h"
#include "./Game.h"

Game::Game(){
    this -> isRunning = false;
}

Game::~Game(){
}

bool Game::IsRunning() const {
    return this -> isRunning;
}

float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 50.0f;
float projectileVelY = 50.0f;

void Game::Initialize(int width, int height){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Error init SDL." << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        "FOO",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std :: cerr << "Error SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(
        window,
        -1,
        0
    );
    if (!renderer){
        std :: cerr << "error SDL renderer." << std::endl;
        return;
    }
    
    isRunning = true;
    return;
};

// INPUT -> UPDATE -> RENDER

void Game::ProcessInput(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            } 
        }
        default: {
            break;
        }
    }
}

void Game::Update(){
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME){
        SDL_Delay(timeToWait);
    }
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    ticksLastFrame = SDL_GetTicks();

    projectilePosX += projectileVelX * deltaTime;
    projectilePosY += projectileVelY * deltaTime;
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_Rect projectile {
        (int) projectilePosX,
        (int) projectilePosY,
        10,
        10
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);

    SDL_RenderPresent(renderer);
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
