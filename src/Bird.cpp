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
      isDead(false),
      flapSound(nullptr),
      hitSound(nullptr),
      rotation(0),
      targetRotation(0),
      rotationSpeed(300.0f),
      downwardRotationSpeed(120.0f) { 
    
    // Load sounds
    flapSound = Mix_LoadWAV("resources/sounds/flap.wav");
    hitSound = Mix_LoadWAV("resources/sounds/hit.wav");
    
    // Set up animation frames
    for (int i = 0; i < 3; ++i) {
        SDL_Rect frame = {i * BIRD_WIDTH, 0, BIRD_WIDTH, BIRD_HEIGHT};
        addFrame(frame);
    }
    
    setFrameTime(0.1f);
    setGravityScale(1.2f);
    setElasticity(0.0f);
    velocityY = 0;
    collisionType = CollisionType::PIXEL;
}

Bird::~Bird() {
    if (flapSound) Mix_FreeChunk(flapSound);
    if (hitSound) Mix_FreeChunk(hitSound);
}

void Bird::update(float deltaTime) {
    if (isDead) return;
    
    AnimatedSprite::update(deltaTime);
    
    // Update rotation based on vertical velocity
    if (velocityY < 0) {
        // Bird is moving up - rotate upward quickly
        targetRotation = -30.0f;
        float rotationDiff = targetRotation - rotation;
        if (abs(rotationDiff) > 0.1f) {
            float rotationChange = rotationSpeed * deltaTime;
            rotation += std::clamp(rotationDiff, -rotationChange, rotationChange);
        }
    } else {
        // Bird is falling - gradually rotate downward
        targetRotation = 90.0f;
        float rotationDiff = targetRotation - rotation;
        if (abs(rotationDiff) > 0.1f) {
            float rotationChange = downwardRotationSpeed * deltaTime;
            rotation += std::clamp(rotationDiff, -rotationChange, rotationChange);
        }
    }
    
    // Clamp rotation to prevent extreme angles
    rotation = std::clamp(rotation, -30.0f, 90.0f);
    
    // Add constraints to keep bird in view and check floor collision
    if (rect.y < 0) {
        rect.y = 0;
        velocityY = 0;
    }
    if (rect.y + rect.h > WINDOW_HEIGHT) {
        rect.y = WINDOW_HEIGHT - rect.h;
        velocityY = 0;
        die();
    }
}

void Bird::render(SDL_Renderer* ren) {
    if (!isActive || !texture) return;
    
    // Create destination rectangle
    SDL_Rect destRect = rect;
    
    // Create a point for rotation center (center of the bird)
    SDL_Point center = {rect.w / 2, rect.h / 2};
    
    // Render the bird with current rotation
    SDL_RenderCopyEx(ren, texture, nullptr, &destRect, rotation, &center, SDL_FLIP_NONE);
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
        velocityY = -400.0f;
        if (flapSound) Mix_PlayChannel(-1, flapSound, 0);
        
        // Immediately set a slight upward rotation when flapping
        rotation = -20.0f;
        targetRotation = -30.0f;
    }
}