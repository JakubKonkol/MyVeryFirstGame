#include "Bullet.h"
#include <SDL2/SDL.h>
Bullet::Bullet(int x, int y, int velx, int vely) {
    mRect.x = x;
    mRect.y = y;
    mRect.w = 8;
    mRect.h = 8;
    velocity_.x = velx;
    velocity_.y = vely;
}
void Bullet::update(double dt) {
    mRect.x += velocity_.x * 250 * dt;
    mRect.y += velocity_.y * 250 * dt;
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &mRect);
}