#include "AnimatedSprite.h"
AnimatedSprite::AnimatedSprite(SDL_Renderer *render, const std::string &path, int xcor, int ycor, int width, int height) : PhysicsSprite(render, path, xcor, ycor, width, height), curentframe(0), frametime(0.1f), frametimer(0), loops(true) {}
void AnimatedSprite::update(float dtime){
    PhysicsSprite::update(dtime);
    if (!frames.empty())
    {
        frametimer += dtime;
        if (frametimer >= frametime)
        {
            frametimer = 0;
            curentframe++;
            if (curentframe >= static_cast<int>(frames.size()))
            {
                if (loops)
                {
                    curentframe = 0;
                }
                else
                {
                    curentframe = static_cast<int>(frames.size()) - 1;
                }
            }
        }
    }
}
void AnimatedSprite::addframe(const SDL_Rect &frame){
    frames.push_back(frame);
}