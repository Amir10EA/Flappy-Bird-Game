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
    int minDistanceFromGround = BIRD_HEIGHT * 2.5; // Minimum distance from ground
    
    // Calculate available space considering only bottom ground
    int totalPlayableHeight = WINDOW_HEIGHT - GROUND_HEIGHT;
    
    // Generate random position for gap with wider range
    // Allow gap to be positioned between 20% and 80% of playable height
    int minGapY = static_cast<int>(totalPlayableHeight * 0.2);
    int maxGapY = static_cast<int>(totalPlayableHeight * 0.8);
    int availableRange = maxGapY - minGapY - gapSize;
    
    int gapStart = minGapY + (rand() % availableRange);
    
    if (isTopPipe) {
        rect.y = 0;  // Start from the very top of the window
        rect.h = gapStart; // Height extends to where the gap starts
    } else {
        rect.y = gapStart + gapSize;
        rect.h = (WINDOW_HEIGHT - GROUND_HEIGHT) - rect.y; // Extend exactly to the ground
    }
}