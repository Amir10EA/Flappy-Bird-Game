#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Bird.h"
#include "Pipe.h"
#include "GameOverScreen.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class GameLevel {
private:
    std::vector<std::unique_ptr<Sprite>> sprites;
    Bird* bird;
    std::vector<Pipe*> pipes;
    int score;
    float difficulty;
    int currentLevel;
    TTF_Font* font;
    SDL_Texture* scoreTexture;
    SDL_Texture* levelTexture;
    std::unique_ptr<GameOverScreen> gameOverScreen;
    float levelUpThreshold;
    SDL_Renderer* renderer;
    Mix_Chunk* levelUpSound;
    SDL_Texture* backgroundTexture;
    float backgroundOffset;
    bool gameStarted;
    int bestScore;
    
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
private:
    void loadBestScore();
    void saveBestScore();
};

#endif