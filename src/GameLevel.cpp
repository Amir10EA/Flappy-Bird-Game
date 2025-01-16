#include "GameLevel.h"
#include <algorithm>

GameLevel::GameLevel(SDL_Renderer* ren)
    : score(0),
      spawnTimer(0),
      difficulty(1.0f),
      isGameOver(false),
      currentLevel(1),
      levelUpThreshold(10),
      renderer(ren) {
    
    // Initialize bird - now using updated constructor with 3 parameters
    bird = new Bird(ren, WINDOW_WIDTH/4, WINDOW_HEIGHT/2);
    sprites.push_back(std::unique_ptr<Sprite>(bird));
    
    // Initialize pipes with proper spacing
    for (int i = 0; i < 3; ++i) {
        int x = WINDOW_WIDTH + (i * PIPE_SPACING);
        Pipe* topPipe = new Pipe(ren, "resources/images/pipe.png", x, 0, true);
        Pipe* bottomPipe = new Pipe(ren, "resources/images/pipe.png", x, 0, false);
        pipes.push_back(topPipe);
        pipes.push_back(bottomPipe);
        sprites.push_back(std::unique_ptr<Sprite>(topPipe));
        sprites.push_back(std::unique_ptr<Sprite>(bottomPipe));
    }
    
    // Initialize font
    font = TTF_OpenFont("resources/fonts/Arial.ttf", 36);
    scoreTexture = nullptr;
    levelTexture = nullptr;
    
    // Initialize game over screen
    gameOverScreen = std::make_unique<GameOverScreen>(ren, font);
    
    // Initial texture updates
    updateScoreTexture(renderer);
    updateLevelTexture(renderer);
}

GameLevel::~GameLevel() {
    // Clean up score texture
    if (scoreTexture) {
        SDL_DestroyTexture(scoreTexture);
    }
    
    // Clean up font
    if (font) {
        TTF_CloseFont(font);
    }
}

void GameLevel::update(float deltaTime) {
    if (!bird->isDying()) {
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
        
        // Update score and level when passing pipes
        for (size_t i = 0; i < pipes.size(); i += 2) {
            if (pipes[i]->getRect().x + PIPE_WIDTH < bird->getRect().x && 
                pipes[i]->getRect().x + PIPE_WIDTH > bird->getRect().x - 5) {
                score++;
                updateScoreTexture(renderer);
                
                // Check for level up
                int newLevel = (score / static_cast<int>(levelUpThreshold)) + 1;
                if (newLevel != currentLevel) {
                    currentLevel = newLevel;
                    difficulty = 1.0f + (currentLevel - 1) * 0.2f;
                    updateLevelTexture(renderer);
                    
                    // Update pipe scroll speeds
                    for (auto pipe : pipes) {
                        pipe->setScrollSpeed(INITIAL_SCROLL_SPEED * difficulty);
                    }
                }
            }
        }
    }
}


void GameLevel::render(SDL_Renderer* ren) {
    // Render all sprites
    for (auto& sprite : sprites) {
        sprite->render(ren);
    }
    
    // Render score at top center
    if (scoreTexture) {
        SDL_Rect panelRect = {
            (WINDOW_WIDTH - 200) / 2,
            20,
            200,
            60
        };
        
        // Draw panel background
        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 180);
        SDL_RenderFillRect(ren, &panelRect);
        
        // Add highlights
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 30);
        SDL_Rect highlightRect = {panelRect.x, panelRect.y, panelRect.w, 2};
        SDL_RenderFillRect(ren, &highlightRect);
        
        // Draw score
        SDL_Rect scoreRect = {
            panelRect.x + (panelRect.w - 100) / 2,
            panelRect.y + (panelRect.h - 40) / 2,
            100,
            40
        };
        SDL_RenderCopy(ren, scoreTexture, nullptr, &scoreRect);
    }
    
    // Render level indicator at top-left
    if (levelTexture) {
        SDL_Rect levelPanelRect = {
            20,
            20,
            150,
            50
        };
        
        // Draw panel background with gradient effect
        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 180);
        SDL_RenderFillRect(ren, &levelPanelRect);
        
        // Add golden border
        SDL_SetRenderDrawColor(ren, 255, 215, 0, 255);
        SDL_RenderDrawRect(ren, &levelPanelRect);
        
        // Draw level text
        SDL_Rect levelTextRect = {
            levelPanelRect.x + 10,
            levelPanelRect.y + 10,
            130,
            30
        };
        SDL_RenderCopy(ren, levelTexture, nullptr, &levelTextRect);
    }
    
    // Render game over screen if game is over
    if (bird->isDying()) {
        gameOverScreen->update(score);
        gameOverScreen->render(ren);
    }
}

void GameLevel::handleInput(const SDL_Event& event) {
    if (bird->isDying()) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (gameOverScreen->isRestartButtonClicked(mouseX, mouseY)) {
                reset();
            }
        }
    } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
        bird->flap();
    }
}

void GameLevel::reset() {
    score = 0;
    currentLevel = 1;
    difficulty = 1.0f;
    
    // Reset bird position and state
    bird->setPosition(WINDOW_WIDTH/4, WINDOW_HEIGHT/2);
    bird->setVelocity(0, 0);
    bird->resetState();
    
    // Reset all pipes with proper spacing
    for (size_t i = 0; i < pipes.size(); i += 2) {
        float spacing = (i/2) * PIPE_SPACING;
        pipes[i]->reset(WINDOW_WIDTH + spacing);
        pipes[i+1]->reset(WINDOW_WIDTH + spacing);
        pipes[i]->setScrollSpeed(INITIAL_SCROLL_SPEED);
        pipes[i+1]->setScrollSpeed(INITIAL_SCROLL_SPEED);
    }
    
    // Update displays
    updateScoreTexture(renderer);
    updateLevelTexture(renderer);
}

void GameLevel::updateScoreTexture(SDL_Renderer* ren) {
    // Clean up existing texture if it exists
    if (scoreTexture) {
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = nullptr;
    }

    // Create score text with current score
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    std::string scoreText = "Score: " + std::to_string(score);
    
    // Create surface from text
    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (!surface) {
        printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        return;
    }
    
    // Create texture from surface
    scoreTexture = SDL_CreateTextureFromSurface(ren, surface);
    if (!scoreTexture) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    
    // Clean up surface
    SDL_FreeSurface(surface);
}

void GameLevel::updateLevelTexture(SDL_Renderer* ren) {
    if (levelTexture) {
        SDL_DestroyTexture(levelTexture);
    }
    
    SDL_Color color = {255, 215, 0, 255}; // Gold color
    std::string levelText = "Level " + std::to_string(currentLevel);
    SDL_Surface* surface = TTF_RenderText_Solid(font, levelText.c_str(), color);
    if (surface) {
        levelTexture = SDL_CreateTextureFromSurface(ren, surface);
        SDL_FreeSurface(surface);
    }
}