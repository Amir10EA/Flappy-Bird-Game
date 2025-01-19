#ifndef PIPE_H
#define PIPE_H
#include "PhysicsSprite.h"
class Pipe : public PhysicsSprite
{
private:
    float scrollspeed;
    bool toppipe;

public:
    Pipe(SDL_Renderer *renderer, const std::string &path, int xcor, int ycor, bool top);
    void update(float time) override;
    void render(SDL_Renderer *renderer) override;
    void reset(int xcor);
    void setScrollSpeed(float speed) { scrollspeed = speed; }
};
#endif