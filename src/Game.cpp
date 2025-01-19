#include "Game.h"
#include <iostream>
#include "keyboard_shortcuts.h"

Game::Game() : GameEngine(){}
Game::~Game(){}
bool Game::initialize(){
    if (!GameEngine::initialize())
    {
        return false;
    }
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
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
            case SDLK_SPACE:
                if (paused && !curentlevel->isGameOver())
                {
                    togglePause(paused);
                    curentlevel->handleInput(event);
                }
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (paused && !curentlevel->isGameOver() && event.button.button == SDL_BUTTON_LEFT)
            {
                togglePause(paused);
                curentlevel->handleInput(event);
            }
            break;
        }

        if (!paused)
        {
            curentlevel->handleInput(event);
        }
    }
}
void Game::update()
{
    float time = (SDL_GetTicks() - lastframetime) / 1000.0f;
    lastframetime = SDL_GetTicks();
    if (time > 0.05f)
    {
        time = 0.05f;
    }
    curentlevel->update(time);
}
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    curentlevel->render(renderer);
    SDL_RenderPresent(renderer);
}