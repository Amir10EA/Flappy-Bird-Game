#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(SDL_Renderer* ren, TTF_Font* gameFont) 
    : font(gameFont), 
      scoreTexture(nullptr), 
      bestScoreTexture(nullptr),
      restartTexture(nullptr), 
      currentScore(0), 
      bestScore(0) {
    
    // Initialize all rectangles with proper positioning
    gameOverRect = {WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT/3, 300, 60};
    scoreRect = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 60, 200, 50};  // Made narrower
    bestScoreRect = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2, 200, 50};   // Made narrower
    buttonRect = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 60, 200, 60};
}
GameOverScreen::~GameOverScreen() {
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (bestScoreTexture) SDL_DestroyTexture(bestScoreTexture);
    if (restartTexture) SDL_DestroyTexture(restartTexture);
}

void GameOverScreen::update(int score) {
    currentScore = score;
    if (score > bestScore) {
        bestScore = score;
    }
}

void GameOverScreen::render(SDL_Renderer* ren) {
    // Fade background
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 200);
    SDL_Rect fullscreen = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(ren, &fullscreen);

    // Create main panel
    SDL_Rect panel = {
        WINDOW_WIDTH/2 - 200,
        WINDOW_HEIGHT/2 - 150,
        400,
        300
    };
    
    // Draw panel with gradient effect
    SDL_SetRenderDrawColor(ren, 45, 45, 48, 255);
    SDL_RenderFillRect(ren, &panel);
    
    // Add golden border
    SDL_SetRenderDrawColor(ren, 255, 215, 0, 255);
    SDL_RenderDrawRect(ren, &panel);

    // Define colors
    SDL_Color titleColor = {255, 215, 0, 255};  // Gold
    SDL_Color textColor = {255, 255, 255, 255}; // White
    SDL_Color highlightColor = {0, 255, 255, 255}; // Cyan

    // Render "Game Over!" with shadow
    SDL_Rect shadowRect = gameOverRect;
    shadowRect.x += 2;
    shadowRect.y += 2;
    SDL_Color shadowColor = {0, 0, 0, 255};
    renderText(ren, "Game Over!", shadowRect, shadowColor);
    renderText(ren, "Game Over!", gameOverRect, titleColor);
    
    // Render score with label
    std::string scoreStr = "Score:" + std::to_string(currentScore);
    std::string bestStr = "Best:" + std::to_string(bestScore);  // Removed space after colon
    
    // Center-align the score text
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), highlightColor);
    if (scoreSurface) {
        SDL_Rect centeredScoreRect = scoreRect;
        centeredScoreRect.w = scoreSurface->w;
        centeredScoreRect.h = scoreSurface->h;
        centeredScoreRect.x = WINDOW_WIDTH/2 - scoreSurface->w/2;
        
        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(ren, scoreSurface);
        SDL_RenderCopy(ren, scoreTexture, nullptr, &centeredScoreRect);
        SDL_DestroyTexture(scoreTexture);
        SDL_FreeSurface(scoreSurface);
    }
    
    // Center-align the best score text
    SDL_Surface* bestSurface = TTF_RenderText_Solid(font, bestStr.c_str(), highlightColor);
    if (bestSurface) {
        SDL_Rect centeredBestRect = bestScoreRect;
        centeredBestRect.w = bestSurface->w;
        centeredBestRect.h = bestSurface->h;
        centeredBestRect.x = WINDOW_WIDTH/2 - bestSurface->w/2;
        
        SDL_Texture* bestTexture = SDL_CreateTextureFromSurface(ren, bestSurface);
        SDL_RenderCopy(ren, bestTexture, nullptr, &centeredBestRect);
        SDL_DestroyTexture(bestTexture);
        SDL_FreeSurface(bestSurface);
    }
    
    // Draw restart button
    SDL_Rect paddedButton = buttonRect;
    
    SDL_SetRenderDrawColor(ren, 76, 175, 80, 255);
    SDL_RenderFillRect(ren, &paddedButton);
    
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 40);
    SDL_RenderDrawRect(ren, &paddedButton);
    
    SDL_Rect textRect = {
        paddedButton.x + 20,
        paddedButton.y + 15,
        paddedButton.w - 40,
        paddedButton.h - 30
    };
    
    SDL_Color buttonTextColor = {255, 255, 255, 255};
    renderText(ren, "Restart", textRect, buttonTextColor);
}
void GameOverScreen::renderText(SDL_Renderer* ren, const std::string& text, SDL_Rect& rect, SDL_Color& color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
        SDL_RenderCopy(ren, texture, nullptr, &rect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
}

bool GameOverScreen::isRestartButtonClicked(int x, int y) const {
    return (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
            y >= buttonRect.y && y <= buttonRect.y + buttonRect.h);
}