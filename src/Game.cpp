#include "Game.h"
#include <iostream>
#include "keyboard_shortcuts.h"

Game::Game() : window(nullptr),
               renderer(nullptr),
               running(false),
               fps(60.0f),
               lastframetime(0),
               paused(false),
               muted(false),
               font(nullptr)
{
}

Game::~Game()
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
bool Game::initialize()
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
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cerr << SDL_GetError() << std::endl;
        return false;
    }
    font = TTF_OpenFont("resources/fonts/PressStart2P.ttf", 20);
    if (!font)
    {
        std::cerr << TTF_GetError() << std::endl;
        return false;
    }
    curentlevel = std::make_unique<GameLevel>(renderer);
    running = true;
    return true;
}

void Game::run()
{
    const float frameDelay = 1000.0f / FPS;
    while (running)
    {
        Uint32 startingframe = SDL_GetTicks();
        handleInput();
        update();
        render();
        Uint32 time = SDL_GetTicks() - startingframe;
        if (time < frameDelay)
        {
            SDL_Delay(static_cast<Uint32>(frameDelay - time));
        }
    }
}
void Game::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_r:
                curentlevel->reset();
                break;
            case SDLK_p:
                if (!curentlevel->isGameOver())
                {
                    togglePause(paused);
                }
                break;
            case SDLK_m:
                toggleMute(muted);
                break;
            case SDLK_UP:
                adjustVolume(10);
                break;
            case SDLK_DOWN:
                adjustVolume(-10);
                break;
            }
            break;
        }
        if (paused)
        {
            if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||
                (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))
            {
                paused = false;
                curentlevel->handleInput(event);
            }
        }
        else
        {
            curentlevel->handleInput(event);
        }
    }
}
void Game::update()
{
    if (!paused)
    {
        float time = (SDL_GetTicks() - lastframetime) / 1000.0f;
        lastframetime = SDL_GetTicks();
        if (time > 0.05f)
        {
            time = 0.05f;
        }
        curentlevel->update(time);
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    curentlevel->render(renderer);
    SDL_RenderPresent(renderer);
}

