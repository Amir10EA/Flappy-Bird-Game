#include "Game.h"
#include <iostream>

Game::Game()
    : window(nullptr),
      renderer(nullptr),
      isRunning(false),
      targetFPS(60.0f),
      lastFrameTime(0),
      isTyping(false) {
          
    menuFont = nullptr;  // Initialize in init() method
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
    
    // Update to use PressStart2P font
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
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                } else if (event.key.keysym.sym == SDLK_r) {
                    currentLevel->reset();
                }
                break;
                
            case SDL_TEXTINPUT:
                if (isTyping) {
                    playerName += event.text.text;
                }
                break;
        }
        
        currentLevel->handleInput(event);
    }
}

void Game::update() {
    float deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();
    
    // Cap delta time to prevent physics issues
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    
    currentLevel->update(deltaTime);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue background
    SDL_RenderClear(renderer);
    
    currentLevel->render(renderer);
    
    // Render player name input if typing
    if (isTyping) {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(menuFont, 
            ("Enter name: " + playerName).c_str(), textColor);
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect textRect = {10, WINDOW_HEIGHT - 40, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, nullptr, &textRect);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
    }
    
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