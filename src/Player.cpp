#include "Player.h"
#include <SDL2/SDL.h>
#include <cmath>
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
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                velocity_.x -= 1;
            break;
            case SDLK_d:
                velocity_.x += 1;
            break;
            case SDLK_w:
                velocity_.y -= 1;
            break;
            case SDLK_s:
                velocity_.y += 1;
            break;
        }
    }

}

// Calculate and update player position
void Player::update(int SCREEN_WIDTH, int SCREEN_HEIGHT, double dt) {
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
    const double friction = 0.1;
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
    std::cout << "Player position: " << mRect.x << " " << mRect.y << std::endl;
    std::cout << "Player velocity: " << velocity_.x << " " << velocity_.y << std::endl;
}


// Render player
void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &mRect);
}
