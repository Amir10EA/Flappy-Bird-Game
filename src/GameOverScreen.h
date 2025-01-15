#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Constants.h"

class GameOverScreen {
private:
    TTF_Font* font;
    SDL_Texture* scoreTexture;
    SDL_Texture* bestScoreTexture;
    SDL_Texture* restartTexture;
    SDL_Rect gameOverRect;
    SDL_Rect scoreRect;
    SDL_Rect bestScoreRect;
    SDL_Rect buttonRect;
    int currentScore;
    int bestScore;

public:
    GameOverScreen(SDL_Renderer* ren, TTF_Font* gameFont);
    ~GameOverScreen();
    
    void update(int score);
    void render(SDL_Renderer* ren);
    bool isRestartButtonClicked(int x, int y) const;

private:
    void renderText(SDL_Renderer* ren, const std::string& text, SDL_Rect& rect, SDL_Color& color);
};

#endif