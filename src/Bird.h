#ifndef BIRD_H
#define BIRD_H

#include "AnimatedSprite.h"
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <cmath>
#include <vector>

class Bird : public AnimatedSprite
{
private:
    float flappower;
    bool dead;
    Mix_Chunk *flaxsound;
    Mix_Chunk *hitsound;
    float rotation;
    float targetrotation;
    float speedrotation;
    float rotationdown;
    std::vector<SDL_Texture *> textures;
    bool gamestarted;
    float initialY;
    float offset;
    float hoverspeed;

public:
    Bird(SDL_Renderer *renderer, int xcor, int ycor);
    ~Bird();
    void render(SDL_Renderer *renderer) override;
    void handleCollision(Sprite *other) override;
    void flap();
    bool isDying() const { return dead; }
    void reset();
    void die();
    Bird(const Bird &) = delete;
    Bird &operator=(const Bird &) = delete;
    void startGame();
    void update(float dTime, bool gameStarted);
};

#endif