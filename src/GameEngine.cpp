#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() : window(nullptr), renderer(nullptr), running(false), fps(60.0f), lastframetime(0), paused(false), muted(false), font(nullptr) {}

GameEngine::~GameEngine()
{
    cleanup();
}
bool GameEngine::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cerr << SDL_GetError() << std::endl;
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        std::cerr << IMG_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() < 0)
    {
        std::cerr << TTF_GetError() << std::endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}
void GameEngine::run()
{
    while (running)
    {
        Uint32 startingframe = SDL_GetTicks();
        handleInput();
        if (!paused)
        {
            update();
        }
        render();
        limitFrameRate(startingframe);
    }
}
void GameEngine::handleInput()
{
}
void GameEngine::update()
{
}
void GameEngine::render()
{
}
void GameEngine::cleanup()
{
    if (font)
    {
        TTF_CloseFont(font);
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
void GameEngine::limitFrameRate(Uint32 frameStart)
{
    const float delay = 1000.0f / fps;
    Uint32 ticks = SDL_GetTicks() - frameStart;
    if (ticks < delay)
    {
        SDL_Delay(static_cast<Uint32>(delay - ticks));
    }
}