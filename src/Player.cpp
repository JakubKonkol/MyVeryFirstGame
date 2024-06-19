#include "Player.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
std::vector<Bullet> bullets;
auto *keys = SDL_GetKeyboardState(NULL);
Player::Player(int x, int y) {
    mRect.x = x; // position x
    mRect.y = y; // position y
    mRect.w = 50;
    mRect.h = 50;
    velocity_.x = 0;
    velocity_.y = 0;

}

// Handle events
void Player::handleEvent(SDL_Event& event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_A:
            velocity_.x = -1;
        break;
        case SDL_SCANCODE_D:
            velocity_.x = 1;
        break;
        case SDL_SCANCODE_W:
            velocity_.y = -1;
        break;
        case SDL_SCANCODE_S:
            velocity_.y = 1;
        break;
        case SDL_SCANCODE_LEFT:
            bullets.push_back(Bullet(mRect.x + mRect.w / 2, mRect.y + mRect.h / 2, -5, 0));
        break;
        case SDL_SCANCODE_RIGHT:
            bullets.push_back(Bullet(mRect.x + mRect.w / 2, mRect.y + mRect.h / 2, 5, 0));
        break;
        case SDL_SCANCODE_UP:
            bullets.push_back(Bullet(mRect.x + mRect.w / 2, mRect.y + mRect.h / 2, 0, -5));
        break;
        case SDL_SCANCODE_DOWN:
            bullets.push_back(Bullet(mRect.x + mRect.w / 2, mRect.y + mRect.h / 2, 0, 5));
        break;
        default:
            break;
    }
    if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_W]) {
        velocity_.x = -1/std::sqrt(2);
        velocity_.y = -1/std::sqrt(2);
    }
    if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_S]) {
        velocity_.x = -1/std::sqrt(2);
        velocity_.y = 1/std::sqrt(2);
    }
    if (keys[SDL_SCANCODE_D] && keys[SDL_SCANCODE_W]) {
        velocity_.x = 1/std::sqrt(2);
        velocity_.y = -1/std::sqrt(2);
    }
    if (keys[SDL_SCANCODE_D] && keys[SDL_SCANCODE_S]) {
        velocity_.x = 1/std::sqrt(2);
        velocity_.y = 1/std::sqrt(2);
    }
    if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_S]) {
        velocity_.y = 0;
    }
    if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_D]) {
        velocity_.x = 0;
    }
}

// Calculate and update player position
void Player::update(int SCREEN_WIDTH, int SCREEN_HEIGHT, double dt, std::vector<Enemy>& enemies) {
    checkBulletEnemyCollision(enemies);

    // Lets limit velocity
    int max_velocity = 5;
    if (velocity_.x > max_velocity) velocity_.x = max_velocity;
    if (velocity_.x < -max_velocity) velocity_.x = -max_velocity;
    if (velocity_.y > max_velocity) velocity_.y = max_velocity;
    if (velocity_.y < -max_velocity) velocity_.y = -max_velocity;

    // Save old position
    int old_x = mRect.x;
    int old_y = mRect.y;

    // Calculate new position
    mRect.x += velocity_.x * 200 * dt;
    mRect.y += velocity_.y * 200 * dt;

    // Check for collision with walls
    if (mRect.x < 0 || mRect.x + mRect.w > SCREEN_WIDTH || mRect.y < 0 || mRect.y + mRect.h > SCREEN_HEIGHT) {
        mRect.x = old_x;
        mRect.y = old_y;
    }

    // Slow down with friction to make it buttery smooth
    const double friction = 0.03;
    if (fabs(velocity_.x) > 0.1) {
        velocity_.x *= 1.0 - friction;
    } else {
        velocity_.x = 0;
    }
    if (fabs(velocity_.y) > 0.1) {
        velocity_.y *= 1.0 - friction;
    } else {
        velocity_.y = 0;
    }

    // Debug
    // std::cout << "Player position: " << mRect.x << " " << mRect.y << std::endl;
    // std::cout << "Player velocity: " << velocity_.x << " " << velocity_.y << std::endl;

    for (auto& bullet : bullets) {
        bullet.update(dt);

        // Check for collision with walls
        if (bullet.mRect.x < 0 || bullet.mRect.x + bullet.mRect.w > SCREEN_WIDTH ||
            bullet.mRect.y < 0 || bullet.mRect.y + bullet.mRect.h > SCREEN_HEIGHT) {
            bullet = bullets.back();
            bullets.pop_back();
            }
    }
}
void Player::checkBulletEnemyCollision(std::vector<Enemy>& enemies) {
    for (auto& bullet : bullets) {
        for (auto& enemy : enemies) {
            if (SDL_HasIntersection(&bullet.mRect, &enemy.mRect)) {
                enemy.isHit = true;
                bullet = bullets.back();
                bullets.pop_back();

                enemy = enemies.back();
                enemies.pop_back();
                break;
            }
        }
    }
}

// Render player
void Player::render(SDL_Renderer* renderer) {
    for (auto& bullet : bullets) {
        bullet.render(renderer);
    }
    SDL_SetRenderDrawColor(renderer, 12, 183, 87, 255);
    SDL_RenderFillRect(renderer, &mRect);
}
