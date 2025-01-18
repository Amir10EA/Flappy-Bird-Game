#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>
#include <functional>
#include "Constants.h"

enum class CollisionType
{
    NONE,
    RECTANGLE,
    PIXEL
};

class Sprite
{
protected:
    SDL_Rect rect;
    SDL_Texture *texture;
    bool isActive;
    bool isCollidable;
    CollisionType collisionType;
    SDL_Surface *surface;
    Sprite(SDL_Renderer *ren, const std::string &path, int x, int y, int w, int h);

public:
    Sprite(const Sprite &) = delete;
    Sprite &operator=(const Sprite &) = delete;
    virtual ~Sprite();
    virtual void update(float deltaTime) = 0;
    virtual void render(SDL_Renderer *ren);
    virtual void handleCollision(Sprite *other) {}
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
};
#endif