#include "Pipe.h"

Pipe::Pipe(SDL_Renderer* ren, const std::string& path, int x, int y, bool isTop)
    : PhysicsSprite(ren, path, x, y, PIPE_WIDTH, WINDOW_HEIGHT),
      scrollSpeed(INITIAL_SCROLL_SPEED),
      isTopPipe(isTop) {
    affectedByGravity = false;
    reset(x);
}

void Pipe::render(SDL_Renderer* ren) {
    if (!isActive || !texture) return;
    
    SDL_Rect destRect = rect;
    if (isTopPipe) {
        // Render top pipe flipped
        SDL_RenderCopyEx(ren, texture, nullptr, &destRect, 180.0, nullptr, SDL_FLIP_NONE);
    } else {
        // Render bottom pipe normally
        SDL_RenderCopy(ren, texture, nullptr, &destRect);
    }
}

void Pipe::update(float deltaTime) {
    rect.x -= static_cast<int>(scrollSpeed);
    
    if (rect.x + rect.w < 0) {
        reset(WINDOW_WIDTH);
    }
}

void Pipe::reset(int x) {
    rect.x = x;
    
    // Adjusted gap positioning with guaranteed minimum space
    int minGap = BIRD_HEIGHT * 3; // Minimum gap is 3 times bird height
    int maxGap = PIPE_GAP;        // Maximum gap defined in Constants.h
    int minDistance = BIRD_HEIGHT * 2; // Minimum distance from screen edges
    
    // Calculate available space
    int availableSpace = WINDOW_HEIGHT - maxGap - (2 * minDistance);
    
    // Generate random position for gap ensuring minimum space
    int gapStart = minDistance + (rand() % (availableSpace / 2));
    
    if (isTopPipe) {
        rect.h = gapStart;
        rect.y = 0;
    } else {
        rect.y = gapStart + maxGap;
        rect.h = WINDOW_HEIGHT - rect.y;
    }
}