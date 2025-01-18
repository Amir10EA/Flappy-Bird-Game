#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "PhysicsSprite.h"
#include <vector>

class AnimatedSprite : public PhysicsSprite {
protected:
    std::vector<SDL_Rect> frames;
    int currentFrame;
    float frameTime;
    float frameTimer;
    bool looping;
    
public:
    AnimatedSprite(SDL_Renderer* ren, const std::string& path, int x, int y, int w, int h);
    
    void update(float deltaTime) override;
    void addFrame(const SDL_Rect& frame);
    void setFrameTime(float time) { frameTime = time; }
    void setLooping(bool loop) { looping = loop; }
};

#endif