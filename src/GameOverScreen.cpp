#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(SDL_Renderer* ren, TTF_Font* gameFont) 
    : font(gameFont), 
      scoreTexture(nullptr), 
      bestScoreTexture(nullptr),
      restartTexture(nullptr), 
      currentScore(0), 
      bestScore(0) {
    
    // Initialize all rectangles with proper positioning
    gameOverRect = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/3, 200, 50};
    scoreRect = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 60, 200, 40};
    bestScoreRect = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2, 200, 40};
    buttonRect = {WINDOW_WIDTH/2 - 60, WINDOW_HEIGHT/2 + 60, 120, 40};
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
    
    // Calculate and render level reached
    int levelReached = (currentScore / 10) + 1;
    
    // Render scores and level
    std::string scoreText = "Final Score: " + std::to_string(currentScore);
    std::string levelText = "Level Reached: " + std::to_string(levelReached);
    std::string bestText = "Best Score: " + std::to_string(bestScore);
    
    renderText(ren, scoreText, scoreRect, highlightColor);
    renderText(ren, levelText, levelRect, textColor);
    renderText(ren, bestText, bestScoreRect, highlightColor);
    
    // Animate restart button
    buttonPulse += 0.05f;
    float scale = 1.0f + 0.05f * sin(buttonPulse);
    
    SDL_Rect animatedButton = buttonRect;
    animatedButton.w = static_cast<int>(buttonRect.w * scale);
    animatedButton.h = static_cast<int>(buttonRect.h * scale);
    animatedButton.x = WINDOW_WIDTH/2 - animatedButton.w/2;
    
    // Draw button with gradient
    SDL_SetRenderDrawColor(ren, 76, 175, 80, 255);
    SDL_RenderFillRect(ren, &animatedButton);
    
    // Render "Restart" text
    SDL_Color buttonTextColor = {255, 255, 255, 255};
    renderText(ren, "Restart", animatedButton, buttonTextColor);
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