#ifndef BIRD_H
#define BIRD_H

#include "AnimatedSprite.h"
#include <SDL2/SDL_mixer.h>
#include <algorithm> // For std::min and std::max
#include <cmath>    // For M_PI and math functions

class Bird : public AnimatedSprite {
private:
    float flapForce;
    bool isDead;
    Mix_Chunk* flapSound;
    Mix_Chunk* hitSound;
    
public:
    Bird(SDL_Renderer* ren, const std::string& path, int x, int y);
    ~Bird();
    
    void update(float deltaTime) override;
    void handleCollision(Sprite* other) override;
    void flap();
    bool isDying() const { return isDead; }
    void resetState() {
        isDead = false;
        velocityY = 0;
    }
    void die();
};

#endif