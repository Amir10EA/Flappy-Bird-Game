#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "PhysicsSprite.h"
#include <vector>

class AnimatedSprite : public PhysicsSprite
{
protected:
    std::vector<SDL_Rect> frames;
    int curentframe;
    float frametime;
    float frametimer;
    bool loops;
    AnimatedSprite(SDL_Renderer *renderer, const std::string &path, int xcor, int ycor, int width, int height);

public:
    void update(float dtime) override;
    void addframe(const SDL_Rect &frame);
    void settimeframe(float time) { frametime = time; }
    void setlooping(bool loop) { loops = loop; }
};

#endif