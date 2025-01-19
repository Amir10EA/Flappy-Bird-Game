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
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        handleShortcut(event);
        if (!paused)
        {
            propagateEvent(event);
        }
    }
}

void GameEngine::handleShortcut(const SDL_Event &event)
{
    if (event.type == SDL_QUIT)
    {
        running = false;
        return;
    }

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            running = false;
            break;
        case SDLK_p:
            paused = !paused;
            break;
        }
    }
}

void GameEngine::update()
{
    float time = (SDL_GetTicks() - lastframetime) / 1000.0f;
    lastframetime = SDL_GetTicks();
    if (time > 0.05f)
    {
        time = 0.05f;
    }
    updateSprites(time);
}

void GameEngine::updateSprites(float time)
{
    auto it = sprites.begin();
    while (it != sprites.end())
    {
        if (!(*it)->isAlive())
        {
            it = sprites.erase(it);
        }
        else
        {
            (*it)->update(time);
            ++it;
        }
    }
}

void GameEngine::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderSprites();
    SDL_RenderPresent(renderer);
}

void GameEngine::renderSprites()
{
    for (const auto &sprite : sprites)
    {
        if (sprite->isAlive())
        {
            sprite->render(renderer);
        }
    }
}

void GameEngine::cleanup()
{
    sprites.clear();
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

void GameEngine::addSprite(std::shared_ptr<Sprite> sprite)
{
    sprites.push_back(sprite);
}

void GameEngine::removeSprite(Sprite *sprite)
{
    auto it = std::find_if(sprites.begin(), sprites.end(),
                           [sprite](const std::shared_ptr<Sprite> &s)
                           { return s.get() == sprite; });
    if (it != sprites.end())
    {
        sprites.erase(it);
    }
}

void GameEngine::propagateEvent(const SDL_Event &event)
{
    for (const auto &sprite : sprites)
    {
        if (sprite->isAlive())
        {
            sprite->handleEvent(event);
        }
    }
}