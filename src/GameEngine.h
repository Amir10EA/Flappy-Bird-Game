#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
#include <vector>
#include "GameLevel.h"
#include "Sprite.h"

class GameEngine {
protected:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    float fps;
    Uint32 lastframetime;
    bool paused;
    bool muted;
    TTF_Font* font;
    std::vector<std::shared_ptr<Sprite>> sprites;

public:
    GameEngine();
    virtual ~GameEngine();
    virtual bool initialize();
    virtual void run();
    virtual void handleInput();
    virtual void update();
    virtual void render();
    virtual void cleanup();
    
    void addSprite(std::shared_ptr<Sprite> sprite);
    void removeSprite(Sprite* sprite);
    const std::vector<std::shared_ptr<Sprite>>& getSprites() const { return sprites; }
    SDL_Renderer* getRenderer() const { return renderer; }
    void handleShortcut(const SDL_Event& event);

protected:
    void limitFrameRate(Uint32 startingframe);
    void updateSprites(float time);
    void renderSprites();
    void propagateEvent(const SDL_Event& event);
};

#endif