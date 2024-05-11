#ifndef BULLET_H
#define BULLET_H
#include <SDL2/SDL.h>

class Bullet {
public:
    Bullet(int x, int y, int velx, int vely);
    void update(double dt);
    void render(SDL_Renderer* renderer);
    SDL_Rect mRect;
private:
    VELOCITY velocity_;
};

#endif // BULLET_H
