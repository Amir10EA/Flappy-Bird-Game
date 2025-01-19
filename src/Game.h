#ifndef GAME_H
#define GAME_H

#include "GameEngine.h"

class Game : public GameEngine {
private:
    std::unique_ptr<GameLevel> curentlevel;

public:
    Game();
    ~Game() override;
    bool initialize() override;
    void handleInput() override;
    void update() override;
    void render() override;
};

#endif