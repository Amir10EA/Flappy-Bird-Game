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
    bool running;
    std::unique_ptr<GameLevel> curentlevel;
    float fps;
    Uint32 lastframetime;
    TTF_Font *font;
    bool paused;
    bool muted;

public:
    Game();
    ~Game();
    bool initialize();
    void run();
    void handleInput();
    void update();
    void render();
    void cleanup();
    bool getPaused() const { return paused; }
};

#endif