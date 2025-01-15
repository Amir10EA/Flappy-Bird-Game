#include "Bird.h"

// Define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Implementation of clamp if std::clamp is not available
template<typename T>
T clamp(T value, T min, T max) {
    return std::min(std::max(value, min), max);
}

Bird::Bird(SDL_Renderer* ren, const std::string& path, int x, int y)
    : AnimatedSprite(ren, path, x, y, BIRD_WIDTH, BIRD_HEIGHT),
      flapForce(FLAP_FORCE),
      isDead(false) {
    
    // Load sounds
    flapSound = Mix_LoadWAV("resources/sounds/flap.wav");
    hitSound = Mix_LoadWAV("resources/sounds/hit.wav");
    
    // Set up animation frames
    for (int i = 0; i < 3; ++i) {
        SDL_Rect frame = {i * BIRD_WIDTH, 0, BIRD_WIDTH, BIRD_HEIGHT};
        addFrame(frame);
    }
    
    setFrameTime(0.1f);
    setGravityScale(1.2f);  // Increased gravity scale
    setElasticity(0.0f);
    velocityY = 0;
    collisionType = CollisionType::PIXEL;  // Enable pixel-perfect collision
}


Bird::~Bird() {
    if (flapSound) Mix_FreeChunk(flapSound);
    if (hitSound) Mix_FreeChunk(hitSound);
}

void Bird::update(float deltaTime) {
    if (isDead) return;
    
    AnimatedSprite::update(deltaTime);
    
    // Add constraints to keep bird in view and check floor collision
    if (rect.y < 0) {
        rect.y = 0;
        velocityY = 0;
    }
    if (rect.y + rect.h > WINDOW_HEIGHT) {
        rect.y = WINDOW_HEIGHT - rect.h;
        velocityY = 0;
        die(); // Call die instead of setting isDead directly
    }
}

void Bird::die() {
    if (!isDead) {
        isDead = true;
        if (hitSound) Mix_PlayChannel(-1, hitSound, 0);
    }
}

void Bird::handleCollision(Sprite* other) {
    die();
}

void Bird::flap() {
    if (!isDead) {
        velocityY = -400.0f; // Adjusted flap force
        if (flapSound) Mix_PlayChannel(-1, flapSound, 0);
    }
}