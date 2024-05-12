#ifndef PLAYER_H
#define PLAYER_H
#include <Enemy.h>
#include <vector>
struct VELOCITY {
    double x;
    double y;
};
#include <SDL2/SDL.h>
#include "Bullet.h"
class Player {
public:
    Player(int x, int y);
    void handleEvent(SDL_Event& event);
    void update(int SCREEN_WIDTH, int SCREEN_HEIGHT, double dt, std::vector<Enemy>& enemies);
    void render(SDL_Renderer* renderer);
    std::vector<Bullet> bullets;
    SDL_Rect mRect;
private:
    VELOCITY velocity_;
    void checkBulletEnemyCollision(std::vector<Enemy>& enemies);

};

#endif //PLAYER_H
