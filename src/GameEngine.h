#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
#include "GameLevel.h"


class GameEngine {
protected:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    float fps;
    Uint32 lastframetime;
    bool paused;
    bool muted;
    TTF_Font* font;


public:
    GameEngine();
    virtual ~GameEngine();
    virtual bool initialize();
    virtual void run();
    virtual void handleInput();
    virtual void update();
    virtual void render();
    virtual void cleanup();


protected:
    void limitFrameRate(Uint32 startingframe);
};


#endif