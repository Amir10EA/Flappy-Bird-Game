#include "PhysicsSprite.h"
#include "Constants.h"

PhysicsSprite::PhysicsSprite(SDL_Renderer* ren, const std::string& path, int x, int y, int w, int h)
    : Sprite(ren, path, x, y, w, h),
      velocityX(0), velocityY(0),
      gravityScale(1.0f),
      elasticity(0.5f),
      affectedByGravity(true) {
}

void PhysicsSprite::update(float deltaTime) {
    if (!isActive) return;
    
    if (affectedByGravity) {
        velocityY += GRAVITY * gravityScale * deltaTime;
        
        // Cap maximum falling speed
        if (velocityY > 1000.0f) {
            velocityY = 1000.0f;
        }
    }
    
    rect.x += static_cast<int>(velocityX * deltaTime);
    rect.y += static_cast<int>(velocityY * deltaTime);
}
void PhysicsSprite::applyForce(float fx, float fy) {
    velocityX += fx;
    velocityY += fy;
}

void PhysicsSprite::setVelocity(float vx, float vy) {
    velocityX = vx;
    velocityY = vy;
}
