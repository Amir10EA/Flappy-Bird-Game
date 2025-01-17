#include "GameLevel.h"
#include <algorithm>
#include <iostream>
using namespace std;

GameLevel::GameLevel(SDL_Renderer* ren)
    : score(0),
      spawnTimer(0),
      difficulty(1.0f),
      isGameOver(false),
      currentLevel(1),
      levelUpThreshold(10),
      renderer(ren),
      backgroundOffset(0) {
    
    SDL_Surface* bgSurface = IMG_Load("resources/images/flappy-bird-background.jpg");
    if (bgSurface) {
        backgroundTexture = SDL_CreateTextureFromSurface(ren, bgSurface);
        SDL_FreeSurface(bgSurface);
    } else {
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
        backgroundTexture = nullptr;
    }
    
    // Initialize bird
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
    
    // Initialize font with increased size (changed from 24 to 28)
    font = TTF_OpenFont("resources/fonts/PressStart2P.ttf", 28);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }
    
    scoreTexture = nullptr;
    levelTexture = nullptr;
    
    // Initialize game over screen with the same font
    gameOverScreen = std::make_unique<GameOverScreen>(ren, font);
    
    // Initial texture updates
    updateScoreTexture(renderer);
    updateLevelTexture(renderer);
}

GameLevel::~GameLevel() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
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
        // Update background scroll
        backgroundOffset += BACKGROUND_SCROLL_SPEED;
        if (backgroundOffset >= 767) {  // Reset when we reach the duplicate point
            backgroundOffset = 0;
        }
        
        // Rest of the update logic remains the same...
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
        // Only check top pipes to avoid double counting
        for (size_t i = 0; i < pipes.size(); i += 2) {
            // Get the pipe's right edge and bird's horizontal center
            float pipeRightEdge = pipes[i]->getRect().x + PIPE_WIDTH;
            float birdCenterX = bird->getRect().x + (bird->getRect().w / 2);
            
            // Score only when bird's center passes pipe's right edge
            if (pipeRightEdge <= birdCenterX && 
                pipeRightEdge > birdCenterX - (INITIAL_SCROLL_SPEED * difficulty)) {
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
    // Render scrolling background
    if (backgroundTexture) {
        SDL_Rect srcRect = {
            static_cast<int>(backgroundOffset), 0,
            WINDOW_WIDTH, WINDOW_HEIGHT
        };
        SDL_Rect destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderCopy(ren, backgroundTexture, &srcRect, &destRect);
    }
    
    // Render all sprites
    for (auto& sprite : sprites) {
        sprite->render(ren);
    }
    
    // Create a single panel for both level and score with increased dimensions
    SDL_Rect panelRect = {
        (WINDOW_WIDTH - 240) / 2,  // Increased from 200 to 240 for wider area
        15,  // Moved up slightly from 20 to 15
        240,  // Increased width
        120   // Increased height from 100 to 120
    };
    
    // Render level at top of panel with larger dimensions
    if (levelTexture) {
        SDL_Rect levelRect = {
            panelRect.x + (panelRect.w - 150) / 2,  // Increased from 120 to 150
            panelRect.y + 15,
            150,  // Increased width
            40    // Increased height from 30 to 40
        };
        SDL_RenderCopy(ren, levelTexture, nullptr, &levelRect);
    }
    
    // Render score directly below level with larger dimensions
    if (scoreTexture) {
        SDL_Rect scoreRect = {
            panelRect.x + (panelRect.w - 130) / 2,  // Increased from 100 to 130
            panelRect.y + 65,  // Adjusted to maintain spacing
            130,  // Increased width
            40    // Increased height from 30 to 40
        };
        SDL_RenderCopy(ren, scoreTexture, nullptr, &scoreRect);
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
    if (scoreTexture) {
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = nullptr;
    }

    // Create score text with label
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    std::string scoreText = "   " + std::to_string(score) + "   ";
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (!surface) {
        printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        return;
    }
    
    scoreTexture = SDL_CreateTextureFromSurface(ren, surface);
    if (!scoreTexture) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    
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