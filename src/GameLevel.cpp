#include "GameLevel.h"
#include <algorithm>

GameLevel::GameLevel(SDL_Renderer* ren)
    : score(0),
      spawnTimer(0),
      difficulty(1.0f) {
    
    // Initialize bird
    bird = new Bird(ren, "resources/images/bird.png", WINDOW_WIDTH/4, WINDOW_HEIGHT/2);
    sprites.push_back(std::unique_ptr<Sprite>(bird));
   
    // Initialize pipes
    int pipeSpacing = WINDOW_WIDTH/2;
    for (int i = 0; i < 3; ++i) {
        int x = WINDOW_WIDTH + i * pipeSpacing;
        Pipe* topPipe = new Pipe(ren, "resources/images/pipe.png", x, 0, true);
        Pipe* bottomPipe = new Pipe(ren, "resources/images/pipe.png", x, 0, false);
        pipes.push_back(topPipe);
        pipes.push_back(bottomPipe);
        sprites.push_back(std::unique_ptr<Sprite>(topPipe));
        sprites.push_back(std::unique_ptr<Sprite>(bottomPipe));
    }
    
    // Initialize font
    font = TTF_OpenFont("resources/fonts/font.ttf", 36);
    scoreTexture = nullptr;
}

GameLevel::~GameLevel() {
    if (font) TTF_CloseFont(font);
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
}

void GameLevel::update(float deltaTime) {
    if (bird->isDying()) return;
    
    // Update all sprites
    for (auto& sprite : sprites) {
        sprite->update(deltaTime);
    }
    
    // Check collisions
    for (auto& sprite : sprites) {
        if (sprite.get() != bird && bird->checkCollision(sprite.get())) {
            bird->handleCollision(sprite.get());
        }
    }
    
    // Update score
    for (size_t i = 0; i < pipes.size(); i += 2) {
        if (pipes[i]->getRect().x + PIPE_WIDTH < bird->getRect().x && 
            pipes[i]->getRect().x + PIPE_WIDTH > bird->getRect().x - 5) {
            score++;
            difficulty += 0.1f;
            // Update pipe scroll speeds
            for (auto pipe : pipes) {
                pipe->setScrollSpeed(INITIAL_SCROLL_SPEED * difficulty);
            }
        }
    }
}

void GameLevel::render(SDL_Renderer* ren) {
    // Render all sprites
    for (auto& sprite : sprites) {
        sprite->render(ren);
    }
    
    // Render score
    updateScoreTexture(ren);
    if (scoreTexture) {
        SDL_Rect scoreRect = {10, 10, 100, 50};
        SDL_RenderCopy(ren, scoreTexture, nullptr, &scoreRect);
    }
}

void GameLevel::handleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
        bird->flap();
    }
}

void GameLevel::updateScoreTexture(SDL_Renderer* ren) {
    if (scoreTexture) {
        SDL_DestroyTexture(scoreTexture);
    }
    
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), color);
    if (surface) {
        scoreTexture = SDL_CreateTextureFromSurface(ren, surface);
        SDL_FreeSurface(surface);
    }
}

void GameLevel::reset() {
    score = 0;
    difficulty = 1.0f;
    bird->setPosition(WINDOW_WIDTH/4, WINDOW_HEIGHT/2);
    bird->setVelocity(0, 0);
    bird->setActive(true);
    
    // Reset pipes
    for (size_t i = 0; i < pipes.size(); i += 2) {
        pipes[i]->reset(WINDOW_WIDTH + i * (WINDOW_WIDTH/2));
        pipes[i+1]->reset(WINDOW_WIDTH + i * (WINDOW_WIDTH/2));
    }
}