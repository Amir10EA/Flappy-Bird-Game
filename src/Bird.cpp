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

Bird::Bird(SDL_Renderer* ren, int x, int y)
    : AnimatedSprite(ren, "resources/images/bird-wing-up.png", x, y, BIRD_WIDTH, BIRD_HEIGHT),
      flapForce(FLAP_FORCE),
      isDead(false),
      flapSound(nullptr),
      hitSound(nullptr),
      rotation(0),
      targetRotation(0),
      rotationSpeed(300.0f),
      downwardRotationSpeed(100.0f) {  // Slightly reduced from 120.0f
    
    // Load sounds
    flapSound = Mix_LoadWAV("resources/sounds/flap.wav");
    hitSound = Mix_LoadWAV("resources/sounds/hit.wav");
    
    // Load additional frame textures
    SDL_Surface* midwaySurface = IMG_Load("resources/images/bird-wing-midway.png");
    SDL_Surface* downSurface = IMG_Load("resources/images/bird-wing-down.png");
    
    if (midwaySurface && downSurface) {
        SDL_Texture* midwayTexture = SDL_CreateTextureFromSurface(ren, midwaySurface);
        SDL_Texture* downTexture = SDL_CreateTextureFromSurface(ren, downSurface);
        
        frameTextures.push_back(texture);             // Wing up
        frameTextures.push_back(midwayTexture);       // Wing midway
        frameTextures.push_back(downTexture);         // Wing down
        frameTextures.push_back(midwayTexture);       // Wing midway again
        
        SDL_FreeSurface(midwaySurface);
        SDL_FreeSurface(downSurface);
        
        SDL_Rect frameRect = {0, 0, BIRD_WIDTH, BIRD_HEIGHT};
        for (int i = 0; i < 4; i++) {
            addFrame(frameRect);
        }
    }
    
    setFrameTime(0.1f);
    setLooping(true);
    setGravityScale(1.0f);    // Kept at 1.0f since we adjusted base gravity
    setElasticity(0.0f);
    velocityY = 0;
    collisionType = CollisionType::PIXEL;
}

Bird::~Bird() {
    if (flapSound) Mix_FreeChunk(flapSound);
    if (hitSound) Mix_FreeChunk(hitSound);
    
    // Free all frame textures except the first one (handled by base class)
    for (size_t i = 1; i < frameTextures.size(); ++i) {
        if (frameTextures[i]) {
            SDL_DestroyTexture(frameTextures[i]);
        }
    }
}

void Bird::update(float deltaTime) {
    if (isDead) return;
    
    // Update animation
    AnimatedSprite::update(deltaTime);
    
    // Update physics and rotation
    PhysicsSprite::update(deltaTime);
    
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
    if (!isActive) return;
    
    // Get the current frame texture based on animation frame
    SDL_Texture* currentTexture = frameTextures[currentFrame];
    if (!currentTexture) return;
    
    // Create destination rectangle
    SDL_Rect destRect = rect;
    
    // Create a point for rotation center (center of the bird)
    SDL_Point center = {rect.w / 2, rect.h / 2};
    
    // Render the bird with current rotation
    SDL_RenderCopyEx(ren, currentTexture, nullptr, &destRect, rotation, &center, SDL_FLIP_NONE);
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