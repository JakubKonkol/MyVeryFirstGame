#include "Enemy.h"
#include <random>

Enemy::Enemy(int x, int y) {
    mRect.x = x;
    mRect.y = y;
    mRect.w = 50;
    mRect.h = 50;
}

void Enemy::update(double dt) {

}
bool Enemy::checkBulletCollision(SDL_Rect bulletRect) {
    if (SDL_HasIntersection(&bulletRect, &mRect)) {
        isHit = true;
        return true;
    }
    return false;
}
void Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 123, 123, 123, 255);
    SDL_RenderFillRect(renderer, &mRect);
}