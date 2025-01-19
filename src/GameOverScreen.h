#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Constants.h"

class GameOverScreen
{
private:
    TTF_Font *font;
    SDL_Texture *scoretexture;
    SDL_Texture *bestscoretexture;
    SDL_Texture *restarttexture;
    SDL_Rect gameoverRect;
    SDL_Rect scoreRect;
    SDL_Rect levelRect;
    SDL_Rect bestscoreRect;
    SDL_Rect buttonRect;
    int curentscore;
    int bestscore;
    

public:
    void setBestScore(int score);
    GameOverScreen(SDL_Renderer *renderer, TTF_Font *font);
    ~GameOverScreen();
    void update(int score);
    void render(SDL_Renderer *renderer);
    bool isRestartButtonClicked(int xcor, int ycor) const;

private:
    void renderText(SDL_Renderer *renderer, const std::string &text, SDL_Rect &rect, SDL_Color &colour);
    void renderPanel(SDL_Renderer *renderer);
};
#endif