#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
#include "../Engine/keyboard_shortcuts.h"
#include "Constants.h"
#include "GameLevel.h"

class Game {
public:
    Game();
    ~Game();
    bool init();
    void run();
    void handleInput();
    void update();
    void render();
    void cleanup();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    float targetFPS;
    Uint32 lastFrameTime;
    bool isPaused;
    bool isMuted; // Move this line after isPaused
    TTF_Font* menuFont; // Move this line before isMuted
};

#endif