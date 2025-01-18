#ifndef BIRD_H
#define BIRD_H

#include "../Engine/AnimatedSprite.h"
#include "Constants.h"
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <cmath>
#include <vector>


class Bird : public AnimatedSprite {
private:
    float flapForce;
    bool isDead;
    Mix_Chunk* flapSound;
    Mix_Chunk* hitSound;
    float rotation;
    float targetRotation;
    float rotationSpeed;
    float downwardRotationSpeed;
    std::vector<SDL_Texture*> frameTextures;  // Store all frame textures
    bool isGameStarted;
    float initialY;  // Store initial Y position for hovering animation
    float hoverOffset;  // Current hover offset
    float hoverSpeed; 
    
public:
    Bird(SDL_Renderer* ren, int x, int y);  // Updated constructor
    ~Bird();
    
   
    void render(SDL_Renderer* ren) override;
    void handleCollision(Sprite* other) override;
    void flap();
    bool isDying() const { return isDead; }
    void resetState() {
        isDead = false;
        velocityY = 0;
    }
    void die();
    
    // Delete copy constructor and assignment operator
    Bird(const Bird&) = delete;
    Bird& operator=(const Bird&) = delete;
    void startGame();
    void update(float deltaTime, bool gameStarted); 
};

#endif