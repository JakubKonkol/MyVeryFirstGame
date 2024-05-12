#ifndef ENEMY_H
#define ENEMY_H
#include <SDL2/SDL.h>


class Enemy {
public:
    Enemy(int x, int y);
    void update(double dt);
    void render(SDL_Renderer* renderer);
    SDL_Rect mRect;
    bool checkBulletCollision(SDL_Rect bulletRect);
    bool isHit = false;

};



#endif //ENEMY_H
