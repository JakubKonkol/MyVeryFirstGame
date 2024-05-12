#include <chrono>
#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <thread>


#include "src/Player.cpp"
#include "src/Bullet.cpp"
#include "src/Enemy.cpp"
#include "src/Particle.cpp"
#include "src/BloodSplash.cpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
std::vector<Enemy> enemies;
std::vector<BloodSplash> bloodSplashes;
void spawnEnemyAtRandomCoordinate() {
    int randomX = std::rand() % SCREEN_WIDTH;
    int randomY = std::rand() % SCREEN_HEIGHT;
    if (randomX > SCREEN_WIDTH - 50) randomX = SCREEN_WIDTH - 50;
    if (randomY > SCREEN_HEIGHT - 50) randomY = SCREEN_HEIGHT - 50;
    enemies.push_back(Enemy(randomX, randomY));
}
int main(int argc, char** argv){

    /*
     * General initialization
     */
    std::cout << "starting game..." << std::endl;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    double dt = 1/60.0;
    double gameTime = 0;
    double timeSinceLastSpawn = 0;
    Uint32 lastTime = SDL_GetTicks();
    bool running = true;


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }
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
        /*
         * Calculating delta time
         */
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        gameTime += dt;
        timeSinceLastSpawn += dt;
        if (timeSinceLastSpawn > 3) {
            spawnEnemyAtRandomCoordinate();
            timeSinceLastSpawn = 0;
        }

        // DEBUG
        // std::cout << "Game time: " << gameTime << std::endl;
        player.update(SCREEN_WIDTH, SCREEN_HEIGHT, dt, enemies);
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer);
        player.render(renderer);

        /*
         * Renderowanie przeciwnikow i sprawdzenie kolizji z pociskami
         */
        for (auto& enemy : enemies) {
            enemy.render(renderer);

            for(auto& bullets : player.bullets){
                if(enemy.checkBulletCollision(bullets.mRect)){
                    enemy.isHit = true;
                }
            }
            if(enemy.isHit) {
                BloodSplash bs(enemy.mRect.x, enemy.mRect.y);
                bloodSplashes.push_back(bs);

                enemy.isHit = false;
            }
        }
        for (auto& bs : bloodSplashes) {
            bs.render(renderer);
            bs.update(dt);
        }

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