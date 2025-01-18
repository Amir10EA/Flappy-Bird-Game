#ifndef PHYSICS_SPRITE_H
#define PHYSICS_SPRITE_H

#include "Sprite.h"
#include <cmath>

class PhysicsSprite : public Sprite {
protected:
    float velocityX, velocityY;
    float gravityScale;
    float elasticity;
    bool affectedByGravity;
    
public:
    PhysicsSprite(SDL_Renderer* ren, const std::string& path, int x, int y, int w, int h);
    
    // Delete copy constructor and assignment operator
    PhysicsSprite(const PhysicsSprite&) = delete;
    PhysicsSprite& operator=(const PhysicsSprite&) = delete;
    
    void update(float deltaTime) override;
    void applyForce(float fx, float fy);
    void setVelocity(float vx, float vy);
    void setGravityScale(float scale) { gravityScale = scale; }
    void setElasticity(float e) { elasticity = e; }
};

#endif