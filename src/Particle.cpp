#include <SDL2/SDL.h>

class Particle {
    SDL_Rect mRect;
    VELOCITY velocity_;
    double lifeTime_ = 2.0;
    double currentLife_ = 0.0;

public: Particle(int x, int y, int velx, int vely) {
        mRect.x = x;
        mRect.y = y;
        mRect.w = 8;
        mRect.h = 8;
        velocity_.x = velx;
        velocity_.y = vely;
    }
    void update(double dt) {
        mRect.x += velocity_.x * 100 * dt;
        mRect.y += velocity_.y * 100 * dt;
        currentLife_ += dt;

        if (currentLife_ >= lifeTime_) {
            mRect.x = -100;
            mRect.y = -100;
        }
    }
    bool isDead() const{
    return currentLife_ >= lifeTime_;
    }
    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderFillRect(renderer, &mRect);
    }
};