#include "Pipe.h"

Pipe::Pipe(SDL_Renderer *ren, const std::string &path, int x, int y, bool isTop)
    : PhysicsSprite(ren, path, x, y, PIPE_WIDTH, WINDOW_HEIGHT),
      scrollSpeed(INITIAL_SCROLL_SPEED),
      isTopPipe(isTop)
{
    affectedByGravity = false;
    reset(x);
}

void Pipe::render(SDL_Renderer *ren)
{
    if (!isActive || !texture)
        return;

    SDL_Rect destRect = rect;
    if (isTopPipe)
    {
        SDL_RenderCopyEx(ren, texture, nullptr, &destRect, 180.0, nullptr, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopy(ren, texture, nullptr, &destRect);
    }
}

void Pipe::update(float deltaTime)
{
    rect.x -= static_cast<int>(scrollSpeed);
    if (rect.x + rect.w < 0)
    {
        reset(rect.x + (3 * PIPE_SPACING));
    }
}

void Pipe::reset(int x)
{
    rect.x = x;
    int gapSize = PIPE_GAP;
    int totalPlayableHeight = WINDOW_HEIGHT - GROUND_HEIGHT;
    int minGapY = static_cast<int>(totalPlayableHeight * 0.2);
    int maxGapY = static_cast<int>(totalPlayableHeight * 0.8);
    int availableRange = maxGapY - minGapY - gapSize;
    int gapStart = minGapY + (rand() % availableRange);
    if (isTopPipe)
    {
        rect.y = 0;
        rect.h = gapStart;
    }
    else
    {
        rect.y = gapStart + gapSize;
        rect.h = (WINDOW_HEIGHT - GROUND_HEIGHT) - rect.y;
    }
}