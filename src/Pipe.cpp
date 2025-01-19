#include "Pipe.h"

Pipe::Pipe(SDL_Renderer *renderer, const std::string &path, int xcor, int ycor, bool top) : PhysicsSprite(renderer, path, xcor, ycor, PIPE_WIDTH, WINDOW_HEIGHT), scrollspeed(INITIAL_SCROLL_SPEED), toppipe(top)
{
    affectedByGravity = false;
    reset(xcor);
}

void Pipe::render(SDL_Renderer *renderer)
{
    if (!isActive || !texture)
        return;

    SDL_Rect destRect = rect;
    if (toppipe)
    {
        SDL_RenderCopyEx(renderer, texture, nullptr, &destRect, 180.0, nullptr, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    }
}

void Pipe::update(float time)
{
    rect.x -= static_cast<int>(scrollspeed);
    if (rect.x + rect.w < 0)
    {
        reset(rect.x + (3 * PIPE_SPACING));
    }
}

void Pipe::reset(int x)
{
    rect.x = x;
    int gapSize = PIPE_GAP;
    int maxheight = WINDOW_HEIGHT - GROUND_HEIGHT;
    int mingapY = static_cast<int>(maxheight * 0.2);
    int maxgapY = static_cast<int>(maxheight * 0.8);
    int availableRange = maxgapY - mingapY - gapSize;
    int startgap = mingapY + (rand() % availableRange);
    if (toppipe)
    {
        rect.y = 0;
        rect.h = startgap;
    }
    else
    {
        rect.y = startgap + gapSize;
        rect.h = (WINDOW_HEIGHT - GROUND_HEIGHT) - rect.y;
    }
}