#ifndef PHYSICS_SPRITE_H
#define PHYSICS_SPRITE_H
#include "Sprite.h"
#include <cmath>

class PhysicsSprite : public Sprite
{
protected:
    float velocityX, velocityY;
    float gravityScale;
    float elasticity;
    bool affectedByGravity;
    PhysicsSprite(SDL_Renderer *renderer, const std::string &path, int xcor, int ycor, int width, int height);

public:
    void update(float time) override;
    void applyForce(float forcex, float forcey);
    void setVelocity(float velx, float vely);
    void setGravityScale(float gscale) { gravityScale = gscale; }
    void setElasticity(float elast) { elasticity = elast; }
};
#endif