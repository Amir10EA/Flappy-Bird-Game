#include "Sprite.h"
#include "Bird.h"
#include <iostream>
#include <cmath>
using namespace std;

Sprite::Sprite(SDL_Renderer *renderer, const string &path, int xcor, int ycor, int width, int height) : isActive(true), isCollidable(true), collisionType(CollisionType::RECTANGLE), surface(nullptr)
{
    rect = {xcor, ycor, width, height};
    surface = IMG_Load(path.c_str());
    if (!surface)
    {
        cerr << IMG_GetError() << endl;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        cerr << SDL_GetError() << endl;
    }
    if (collisionType != CollisionType::PIXEL)
    {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
}

Sprite::~Sprite()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
    if (surface)
    {
        SDL_FreeSurface(surface);
    }
}

void Sprite::render(SDL_Renderer *renderer)
{
    if (isActive && texture)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}

bool Sprite::checkCollision(Sprite *other)
{
    if (!isActive || !other->isActive || !isCollidable)
        return false;
    if (collisionType == CollisionType::PIXEL && other->collisionType == CollisionType::PIXEL)
    {
        return checkPixelCollision(other);
    }
    const SDL_Rect &r1 = rect;
    const SDL_Rect &r2 = other->getRect();
    return (r1.x < r2.x + r2.w && r1.x + r1.w > r2.x && r1.y < r2.y + r2.h && r1.y + r1.h > r2.y);
}

bool Sprite::checkPixelCollision(Sprite *other)
{
    if (!surface || !other->surface)
        return false;
    SDL_Rect overlap;
    overlap.x = max(rect.x, other->rect.x);
    overlap.y = max(rect.y, other->rect.y);
    overlap.w = min(rect.x + rect.w, other->rect.x + other->rect.w) - overlap.x;
    overlap.h = min(rect.y + rect.h, other->rect.y + other->rect.h) - overlap.y;
    if (overlap.w <= 0 || overlap.h <= 0)
        return false;

    SDL_LockSurface(surface);
    SDL_LockSurface(other->surface);

    bool collision = false;
    float rotation = 0.0f;
    bool isBird = dynamic_cast<Bird *>(this) != nullptr;

    if (isBird)
    {
        Bird *bird = static_cast<Bird *>(this);
        rotation = bird->getRotation() * static_cast<float>(3.14) / 180.0f;
    }

    float centerX = rect.w / 2.0f;
    float centerY = rect.h / 2.0f;

    for (int y = 0; y < overlap.h && !collision; ++y)
    {
        for (int x = 0; x < overlap.w && !collision; ++x)
        {
            int x1 = overlap.x - rect.x + x;
            int y1 = overlap.y - rect.y + y;
            int x2 = overlap.x - other->rect.x + x;
            int y2 = overlap.y - other->rect.y + y;
            if (isBird)
            {
                float dx = x1 - centerX;
                float dy = y1 - centerY;
                x1 = static_cast<int>(centerX + (dx * cos(rotation) - dy * sin(rotation)));
                y1 = static_cast<int>(centerY + (dx * sin(rotation) + dy * cos(rotation)));
            }
            if (x1 >= 0 && x1 < rect.w && y1 >= 0 && y1 < rect.h &&
                x2 >= 0 && x2 < other->rect.w && y2 >= 0 && y2 < other->rect.h)
            {
                Uint32 *pixels1 = static_cast<Uint32 *>(surface->pixels);
                Uint32 *pixels2 = static_cast<Uint32 *>(other->surface->pixels);
                int pitch1 = surface->pitch / 4;
                int pitch2 = other->surface->pitch / 4;
                Uint32 pixel1 = pixels1[y1 * pitch1 + x1];
                Uint32 pixel2 = pixels2[y2 * pitch2 + x2];
                Uint8 alpha1 = (pixel1 >> 24) & 0xFF;
                Uint8 alpha2 = (pixel2 >> 24) & 0xFF;
                if (alpha1 > 127 && alpha2 > 127)
                {
                    collision = true;
                }
            }
        }
    }
    SDL_UnlockSurface(surface);
    SDL_UnlockSurface(other->surface);
    return collision;
}