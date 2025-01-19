#include "PhysicsSprite.h"
#include "Constants.h"

PhysicsSprite::PhysicsSprite(SDL_Renderer *renderer, const std::string &path, int xcor, int ycor, int width, int height)
    : Sprite(renderer, path, xcor, ycor, width, height),
      velocityX(0), velocityY(0),
      gravityScale(1.0f),
      elasticity(0.5f),
      affectedByGravity(true)
{
}
void PhysicsSprite::update(float time)
{
    if (!isActive)
        return;
    if (affectedByGravity)
    {
        velocityY += GRAVITY * gravityScale * time;
        if (velocityY > 1000.0f)
        {
            velocityY = 1000.0f;
        }
    }
    rect.x += static_cast<int>(velocityX * time);
    rect.y += static_cast<int>(velocityY * time);
}
void PhysicsSprite::applyForce(float forcex, float forcey)
{
    velocityX += forcex;
    velocityY += forcey;
}
void PhysicsSprite::setVelocity(float velocityx, float velocityy)
{
    velocityX = velocityx;
    velocityY = velocityy;
}