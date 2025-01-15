// #include "Player.h"

// Player::Player(SDL_Renderer* ren, const std::string& path, int x, int y)
//     : MovingSprite(ren, path, x, y, PLAYER_WIDTH, PLAYER_HEIGHT, ObjectType::PLAYER),
//       canJump(true), score(0), health(100), currentFrame(0), frameDelay(5), frameCounter(0) {
//     loadAnimationFrames(ren);
// }

// Player::~Player() {
//     for (auto frame : animFrames) {
//         SDL_DestroyTexture(frame);
//     }
// }

// void Player::loadAnimationFrames(SDL_Renderer* ren) {
//     // In a real game, you'd load multiple frames
//     // For now, we'll just use the base texture
//     animFrames.push_back(texture);
// }

// void Player::update() {
//     MovingSprite::update();
    
//     // Animation update
//     frameCounter++;
//     if (frameCounter >= frameDelay) {
//         frameCounter = 0;
//         currentFrame = (currentFrame + 1) % animFrames.size();
//     }
// }

// void Player::handleCollision(Sprite* other) {
//     SDL_Rect otherRect = other->getRect();
    
//     switch(other->getType()) {
//         case ObjectType::PLATFORM:
//             if (velocityY > 0 && rect.y + rect.h >= otherRect.y &&
//                 rect.y < otherRect.y && rect.x + rect.w > otherRect.x &&
//                 rect.x < otherRect.x + otherRect.w) {
//                 rect.y = otherRect.y - rect.h;
//                 velocityY = 0;
//                 isOnGround = true;
//                 canJump = true;
//             }
//             break;
            
//         case ObjectType::COLLECTIBLE:
//             score += 10;
//             break;
            
//         case ObjectType::ENEMY:
//             health -= 10;
//             break;
//     }
// }

// void Player::handleInput(const SDL_Event& event) {
//     if (event.type == SDL_KEYDOWN) {
//         switch (event.key.keysym.sym) {
//             case SDLK_LEFT:
//                 velocityX = -MOVE_SPEED;
//                 break;
//             case SDLK_RIGHT:
//                 velocityX = MOVE_SPEED;
//                 break;
//             case SDLK_SPACE:
//                 if (canJump) {
//                     velocityY = JUMP_FORCE;
//                     isOnGround = false;
//                     canJump = false;
//                 }
//                 break;
//         }
//     }
//     else if (event.type == SDL_KEYUP) {
//         switch (event.key.keysym.sym) {
//             case SDLK_LEFT:
//                 if (velocityX < 0) velocityX = 0;
//                 break;
//             case SDLK_RIGHT:
//                 if (velocityX > 0) velocityX = 0;
//                 break;
//         }
//     }
// }

// void Player::render(SDL_Renderer* ren) {
//     if (isActive && !animFrames.empty()) {
//         SDL_RenderCopy(ren, animFrames[currentFrame], nullptr, &rect);
//     }
// }