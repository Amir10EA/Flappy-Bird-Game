// #ifndef PLAYER_H
// #define PLAYER_H

// #include "MovingSprite.h"
// #include <vector>

// class Player : public MovingSprite {
// private:
//     bool canJump;
//     int score;
//     int health;
//     std::vector<SDL_Texture*> animFrames;
//     int currentFrame;
//     int frameDelay;
//     int frameCounter;
    
// public:
//     Player(SDL_Renderer* ren, const std::string& path, int x, int y);
//     ~Player();
    
//     void update() override;
//     void handleCollision(Sprite* other) override;
//     void handleInput(const SDL_Event& event);
//     void render(SDL_Renderer* ren) override;
//     void loadAnimationFrames(SDL_Renderer* ren);
    
//     int getScore() const { return score; }
//     int getHealth() const { return health; }
// };

// #endif