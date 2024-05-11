#ifndef PLAYER_H
#define PLAYER_H
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
    void update(int SCREEN_WIDTH, int SCREEN_HEIGHT, double dt);
    void render(SDL_Renderer* renderer);

private:
    SDL_Rect mRect;
    VELOCITY velocity_;
    std::vector<Bullet> bullets;

};

#endif //PLAYER_H
