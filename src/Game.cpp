#include "Game.h"
#include <iostream>
#include "keyboard_shortcuts.h"

Game::Game()
    : window(nullptr),
      renderer(nullptr),
      isRunning(false),
      targetFPS(60.0f),
      lastFrameTime(0),
      isPaused(false),
      isMuted(false),
      menuFont(nullptr) {
}

Game::~Game() {
    cleanup();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        std::cerr << "SDL_image initialization failed: " << IMG_GetError() << std::endl;
        return false;
    }
    
    if (TTF_Init() < 0) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        return false;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow("Flappy Bird Clone",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WINDOW_WIDTH,
                            WINDOW_HEIGHT,
                            SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    menuFont = TTF_OpenFont("resources/fonts/PressStart2P.ttf", 20);
    if (!menuFont) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    
    currentLevel = std::make_unique<GameLevel>(renderer);
    isRunning = true;
    
    return true;
}

void Game::run() {
    const float frameDelay = 1000.0f / targetFPS;
    
    while (isRunning) {
        Uint32 frameStart = SDL_GetTicks();
        
        handleInput();
        update();
        render();
        
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(static_cast<Uint32>(frameDelay - frameTime));
        }
    }
}

void Game::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                    case SDLK_r:
                        currentLevel->reset();
                        break;
                    case SDLK_p:
                        togglePause(isPaused);
                        break;
                    case SDLK_m:
                        toggleMute(isMuted);
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
        
        if (!isPaused) {
            currentLevel->handleInput(event);
        }
    }
}

void Game::update() {
    if (!isPaused) {
        float deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
        lastFrameTime = SDL_GetTicks();
        
        if (deltaTime > 0.05f) {
            deltaTime = 0.05f;
        }
        
        currentLevel->update(deltaTime);
    }
}

void Game::render() {
    // Removed sky blue background since we use a background image
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Simple black background as fallback
    SDL_RenderClear(renderer);
    
    currentLevel->render(renderer);
    
    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    if (menuFont) {
        TTF_CloseFont(menuFont);
    }
    
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    
    if (window) {
        SDL_DestroyWindow(window);
    }
    
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}