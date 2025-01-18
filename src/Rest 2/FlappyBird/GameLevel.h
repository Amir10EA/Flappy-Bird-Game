#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "../Engine/PhysicsSprite.h"
#include "Constants.h"
#include "Bird.h"
#include "Pipe.h"
#include "GameOverScreen.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class GameLevel {
public:
    GameLevel(SDL_Renderer* ren);
    ~GameLevel();
    void update(float deltaTime);
    void render(SDL_Renderer* ren);
    void handleInput(const SDL_Event& event);
    void reset();
    void loadBestScore();
    void saveBestScore();

private:
    int score;
    int bestScore; // Move this line after score
    float difficulty; // Move this line before bestScore
    int currentLevel;
    int levelUpThreshold;
    SDL_Renderer* renderer;
    float backgroundOffset;
    bool gameStarted; // Move this line after backgroundOffset
    Mix_Chunk* levelUpSound; // Move this line before gameStarted
    Bird* bird;
    std::vector<std::unique_ptr<Sprite>> sprites;
    std::vector<Pipe*> pipes;
    TTF_Font* font;
    SDL_Texture* scoreTexture;
    SDL_Texture* levelTexture;
    std::unique_ptr<GameOverScreen> gameOverScreen;

    void updateScoreTexture(SDL_Renderer* ren);
    void updateLevelTexture(SDL_Renderer* ren);
};

#endif