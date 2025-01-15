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
    // Semi-transparent background
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 128);
    SDL_Rect fullscreen = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(ren, &fullscreen);

    SDL_Color textColor = {255, 255, 255, 255};
    
    // Render "Game Over" text
    renderText(ren, "Game Over!", gameOverRect, textColor);
    
    // Render current score
    std::string scoreText = "Score: " + std::to_string(currentScore);
    renderText(ren, scoreText, scoreRect, textColor);
    
    // Render best score
    std::string bestText = "Best: " + std::to_string(bestScore);
    renderText(ren, bestText, bestScoreRect, textColor);
    
    // Draw restart button with green background
    SDL_SetRenderDrawColor(ren, 76, 175, 80, 255);
    SDL_RenderFillRect(ren, &buttonRect);
    
    // Render "Restart" text on button
    SDL_Color buttonTextColor = {255, 255, 255, 255};
    SDL_Rect restartTextRect = buttonRect;
    restartTextRect.y += 5; // Adjust text position within button
    renderText(ren, "Restart", restartTextRect, buttonTextColor);
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