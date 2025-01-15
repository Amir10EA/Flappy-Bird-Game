// #include "MovingSprite.h"

// MovingSprite::MovingSprite(SDL_Renderer* ren, const std::string& path, int x, int y, int w, int h, ObjectType t)
//     : Sprite(ren, path, x, y, w, h, t), velocityX(0), velocityY(0), acceleration(0), isOnGround(false) {}

// void MovingSprite::update() {
//     applyGravity();
//     rect.x += static_cast<int>(velocityX);
//     rect.y += static_cast<int>(velocityY);
    
//     // Keep sprite in bounds
//     if (rect.x < 0) rect.x = 0;
//     if (rect.x > WINDOW_WIDTH - rect.w) rect.x = WINDOW_WIDTH - rect.w;
//     if (rect.y > WINDOW_HEIGHT - rect.h) {
//         rect.y = WINDOW_HEIGHT - rect.h;
//         velocityY = 0;
//         isOnGround = true;
//     }
// }

// void MovingSprite::applyGravity() {
//     if (!isOnGround) {
//         velocityY += GRAVITY;
//     }
// }

// void MovingSprite::setVelocity(float vx, float vy) {
//     velocityX = vx;
//     velocityY = vy;
// }