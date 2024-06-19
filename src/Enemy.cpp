#include "Enemy.h"
#include <random>

Enemy::Enemy(int x, int y) {
    mRect.x = x;
    mRect.y = y;
    mRect.w = 50;
    mRect.h = 50;
}

void Enemy::update(double dt, int playerX, int playerY) {
    int speed = 100;
    int deltaX = playerX - mRect.x;
    int deltaY = playerY - mRect.y;
    
    double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    
    if (distance > 0) {
        double dirX = deltaX / distance;
        double dirY = deltaY / distance;

        mRect.x += static_cast<int>(dirX * speed * dt);
        mRect.y += static_cast<int>(dirY * speed * dt);
    }
}
bool Enemy::checkBulletCollision(SDL_Rect bulletRect) {
    if (SDL_HasIntersection(&bulletRect, &mRect)) {
        isHit = true;
        return true;
    }
    return false;
}
bool Enemy::checkPlayerCollision(SDL_Rect playerRect) {
    if (SDL_HasIntersection(&playerRect, &mRect)) {
        return true;
    }
    return false;
}
void Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 6, 66, 166, 255);
    SDL_RenderFillRect(renderer, &mRect);
}