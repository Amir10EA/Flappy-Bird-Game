#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>
#include <functional>
#include "Constants.h"

class GameEngine;

enum class CollisionType {
    NONE,
    RECTANGLE,
    PIXEL
};

class Sprite {
protected:
    SDL_Rect rect;
    SDL_Texture* texture;
    bool isActive;
    bool isCollidable;
    CollisionType collisionType;
    SDL_Surface* surface;
    GameEngine* gameEngine;
    Sprite(SDL_Renderer* renderer, const std::string& path, int xcor, int ycor, int width, int height);

private:
    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;

public:
    virtual ~Sprite();
    virtual void update(float time) = 0;
    virtual void render(SDL_Renderer *renderer);
    virtual void handleCollision(Sprite *other) {}
    virtual void handleEvent(const SDL_Event& event) {}
    bool checkCollision(Sprite *other);
    bool checkPixelCollision(Sprite *other);
    SDL_Rect getRect() const { return rect; }
    bool isAlive() const { return isActive; }
    void setActive(bool active) { isActive = active; }
    void setPosition(int x, int y)
    {
        rect.x = x;
        rect.y = y;
    }
    void setGameEngine(GameEngine* engine) { gameEngine = engine; }
    GameEngine* getGameEngine() const { return gameEngine; }
};
#endif