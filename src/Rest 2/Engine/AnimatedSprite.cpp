#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(SDL_Renderer* ren, const std::string& path, int x, int y, int w, int h)
    : PhysicsSprite(ren, path, x, y, w, h),
      currentFrame(0),
      frameTime(0.1f),
      frameTimer(0),
      looping(true) {
}

void AnimatedSprite::update(float deltaTime) {
    PhysicsSprite::update(deltaTime);
    
    if (!frames.empty()) {
        frameTimer += deltaTime;
        if (frameTimer >= frameTime) {
            frameTimer = 0;
            currentFrame++;
            if (currentFrame >= static_cast<int>(frames.size())) {
                if (looping) {
                    currentFrame = 0;
                } else {
                    currentFrame = static_cast<int>(frames.size()) - 1;
                }
            }
        }
    }
}

void AnimatedSprite::addFrame(const SDL_Rect& frame) {
    frames.push_back(frame);
}