#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>
#include <memory>
#include "Bird.h"
#include "Pipe.h"
#include <SDL2/SDL_ttf.h>

class GameLevel {
private:
    std::vector<std::unique_ptr<Sprite>> sprites;
    Bird* bird;
    std::vector<Pipe*> pipes;
    int score;
    float spawnTimer;
    float difficulty;
    TTF_Font* font;
    SDL_Texture* scoreTexture;
    
public:
    GameLevel(SDL_Renderer* ren);
    ~GameLevel();
    
    void update(float deltaTime);
    void render(SDL_Renderer* ren);
    void handleInput(const SDL_Event& event);
    void reset();
    int getScore() const { return score; }
    void updateScoreTexture(SDL_Renderer* ren);
};

#endif