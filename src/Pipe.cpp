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
    
    // When pipe goes off screen, reset it to a position after the last pipe
    if (rect.x + rect.w < 0) {
        reset(rect.x + (3 * PIPE_SPACING)); // Reset 3 pipe-spacings ahead
    }
}

void Pipe::reset(int x) {
    rect.x = x;
    
    // Calculate gap size based on bird height
    int gapSize = PIPE_GAP;
    int minDistance = BIRD_HEIGHT * 2; // Minimum distance from screen edges
    
    // Calculate available space
    int availableSpace = WINDOW_HEIGHT - gapSize - (2 * minDistance);
    
    // Generate random position for gap
    int gapStart = minDistance + (rand() % (availableSpace / 2));
    
    if (isTopPipe) {
        rect.h = gapStart;
        rect.y = 0;
    } else {
        rect.y = gapStart + gapSize;
        rect.h = WINDOW_HEIGHT - rect.y;
    }
}