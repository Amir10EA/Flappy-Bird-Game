#ifndef PIPE_H
#define PIPE_H

#include "PhysicsSprite.h"

class Pipe : public PhysicsSprite {
private:
    float scrollSpeed;
    bool isTopPipe;
    
public:
    Pipe(SDL_Renderer* ren, const std::string& path, int x, int y, bool isTop);
    
    void update(float deltaTime) override;
    void render(SDL_Renderer* ren) override; // Add render method
    void reset(int x);
    void setScrollSpeed(float speed) { scrollSpeed = speed; }
};

#endif 