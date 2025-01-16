#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>
#include <memory>
#include "Bird.h"
#include "Pipe.h"
#include "GameOverScreen.h"
#include <SDL2/SDL_ttf.h>

class GameLevel {
private:
    private:
    std::vector<std::unique_ptr<Sprite>> sprites;
    Bird* bird;
    std::vector<Pipe*> pipes;
    int score;
    float spawnTimer;
    float difficulty;
    int currentLevel;           // Track current level
    bool isGameOver;
    TTF_Font* font;
    SDL_Texture* scoreTexture;
    SDL_Texture* levelTexture;  // New texture for level display
    std::unique_ptr<GameOverScreen> gameOverScreen;
    float levelUpThreshold;     // Points needed for level up
    SDL_Renderer* renderer;
    
public:
    GameLevel(SDL_Renderer* ren);
    ~GameLevel();
    
    void update(float deltaTime);
    void render(SDL_Renderer* ren);
    void handleInput(const SDL_Event& event);
    void reset();
    int getScore() const { return score; }
    int getCurrentLevel() const { return currentLevel; }
    void updateScoreTexture(SDL_Renderer* ren);
    void updateLevelTexture(SDL_Renderer* ren);
};
#endif