#include <SDL2/SDL.h>

class BloodSplash {
public:
    std::vector<Particle> particles;

    BloodSplash(int x, int y) {
        for (int i = 0; i < 1000; i++) {
            int velX = std::rand() % 100 - 50;
            int velY = std::rand() % 100 - 50;
            int newX = x + std::rand() % 5 - 10;
            int newY = y + std::rand() % 5 - 10;
            particles.push_back(Particle(newX, newY, velX, velY));
        }
    }

    void update(double dt) {
        for (auto it = particles.begin(); it != particles.end(); ) {
            it->update(dt);
            if (it->isDead()) {
                it = particles.erase(it);
            } else {
                ++it;
            }
        }
    }

void render(SDL_Renderer* renderer) {
        for (auto& particle : particles) {
            particle.render(renderer);
        }
    }
};