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

class GameLevel
{
private:
    std::vector<std::unique_ptr<Sprite>> sprites;
    Bird *bird;
    std::vector<Pipe *> pipes;
    int score;
    float difficulty;
    int curentlevel;
    TTF_Font *font;
    SDL_Texture *scoretexture;
    SDL_Texture *leveltexture;
    std::unique_ptr<GameOverScreen> gameoverscreen;
    float levelupthreshold;
    SDL_Renderer *renderer;
    Mix_Chunk *levelupsound;
    SDL_Texture *backgroundtexture;
    float backgroundoffset;
    bool started;
    int bestScore;

public:
    GameLevel(SDL_Renderer *renderer);
    ~GameLevel();
    void update(float time);
    void render(SDL_Renderer *renderer);
    void handleInput(const SDL_Event &event);
    void reset();
    int getScore() const { return score; }
    int getCurrentLevel() const { return curentlevel; }
    void updateScoreTexture(SDL_Renderer *renderer);
    void updateLevelTexture(SDL_Renderer *renderer);
    bool isGameOver() const { return bird->isDying(); }
private:
    void loadBestScore();
    void saveBestScore();
};

#endif