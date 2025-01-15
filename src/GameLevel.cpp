#include "GameLevel.h"
#include <algorithm>

GameLevel::GameLevel(SDL_Renderer* ren)
    : score(0),
      spawnTimer(0),
      difficulty(1.0f),
      isGameOver(false) {  // Add this line
    
    // Initialize bird
    bird = new Bird(ren, "resources/images/bird.png", WINDOW_WIDTH/4, WINDOW_HEIGHT/2);
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
    
    // Initialize game over screen
    gameOverScreen = std::make_unique<GameOverScreen>(ren, font);
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
        
        // Update score when passing pipes
        for (size_t i = 0; i < pipes.size(); i += 2) {
            if (pipes[i]->getRect().x + PIPE_WIDTH < bird->getRect().x && 
                pipes[i]->getRect().x + PIPE_WIDTH > bird->getRect().x - 5) {
                score++;
                updateScoreTexture(renderer); // Update score display immediately
                difficulty += 0.1f;
                
                // Update pipe scroll speeds
                for (auto pipe : pipes) {
                    pipe->setScrollSpeed(INITIAL_SCROLL_SPEED * difficulty);
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
    
    // Render score at top of screen with a nice background and animation
    if (scoreTexture) {
        // Create a semi-transparent dark background panel
        SDL_Rect panelRect = {
            (WINDOW_WIDTH - 200) / 2,  // Center horizontally
            20,                        // 20 pixels from top
            200,                       // Fixed width
            60                         // Fixed height
        };
        
        // Render panel background with rounded corners effect
        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 180);
        SDL_RenderFillRect(ren, &panelRect);
        
        // Add highlights to make it look more 3D
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 30);
        SDL_Rect highlightRect = {panelRect.x, panelRect.y, panelRect.w, 2};
        SDL_RenderFillRect(ren, &highlightRect);
        
        // Calculate score position for smooth animation
        SDL_Rect scoreRect = {
            panelRect.x + (panelRect.w - 100) / 2,  // Center in panel
            panelRect.y + (panelRect.h - 40) / 2,   // Center vertically
            100,                                     // Width
            40                                       // Height
        };
        
        // Add a subtle bounce animation when score changes
        static int lastScore = score;
        if (lastScore != score) {
            static float bounceOffset = 0;
            bounceOffset = 5.0f;  // Start bounce
            lastScore = score;
        }
        
        // Render the score
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
    
    // Update score display
    updateScoreTexture(renderer);
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