#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
#include "GameLevel.h"

class Game
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool isRunning;
    std::unique_ptr<GameLevel> currentLevel;
    float targetFPS;
    Uint32 lastFrameTime;
    TTF_Font *menuFont;
    bool isPaused;
    bool isMuted;

public:
    Game();
    ~Game();
    bool init();
    void run();
    void handleInput();
    void update();
    void render();
    void cleanup();
    bool isPauseActive() const { return isPaused; }
};

#endif