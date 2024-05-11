#include <chrono>
#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <thread>


#include "src/Player.cpp"
#include "src/Bullet.cpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(int argc, char** argv){
    std::cout << "starting game..." << std::endl;
    SDL_Window *window;
    SDL_Renderer *renderer;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }
    Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    double dt = 1/60.0;
    double gameTime = 0;
    Uint32 lastTime = SDL_GetTicks();
    bool running = true;
    // GAME LOOP
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                break;
                case SDL_KEYUP:
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) running = false;
                break;

                default:
                    player.handleEvent(event);
                    break;
            }
        }
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        gameTime += dt;
        // DEBUG
        std::cout << "Game time: " << gameTime << std::endl;
        player.update(SCREEN_WIDTH, SCREEN_HEIGHT, dt);
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer);
        player.render(renderer);
        SDL_RenderPresent(renderer);

        // Delays
        if (deltaTime < 1000/60) {
            SDL_Delay((1000/60) - deltaTime);
        }
    }
    std::cout << "Quiting game...." << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}