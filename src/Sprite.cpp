#include "Sprite.h"
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, const std::string& path, int xcor, int ycor, int width, int height)
    : isActive(true), isCollidable(true), collisionType(CollisionType::RECTANGLE), surface(nullptr)
{
    rect = {xcor, ycor, width, height};
    surface = IMG_Load(path.c_str());
    if (!surface)
    {
        std::cerr <<  IMG_GetError() << std::endl;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        std::cerr << SDL_GetError() << std::endl;
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
    return (r1.x < r2.x + r2.w &&
            r1.x + r1.w > r2.x &&
            r1.y < r2.y + r2.h &&
            r1.y + r1.h > r2.y);
}

bool Sprite::checkPixelCollision(Sprite *other)
{
    if (!surface || !other->surface)
        return false;
    SDL_Rect overlap;
    overlap.x = std::max(rect.x, other->rect.x);
    overlap.y = std::max(rect.y, other->rect.y);
    overlap.w = std::min(rect.x + rect.w, other->rect.x + other->rect.w) - overlap.x;
    overlap.h = std::min(rect.y + rect.h, other->rect.y + other->rect.h) - overlap.y;
    if (overlap.w <= 0 || overlap.h <= 0)
        return false;
    for (int y = 0; y < overlap.h; ++y)
    {
        for (int x = 0; x < overlap.w; ++x)
        {
            int x1 = overlap.x - rect.x + x;
            int y1 = overlap.y - rect.y + y;
            int x2 = overlap.x - other->rect.x + x;
            int y2 = overlap.y - other->rect.y + y;
            Uint32 *pixels1 = (Uint32 *)surface->pixels;
            Uint32 *pixels2 = (Uint32 *)other->surface->pixels;
            Uint32 pixel1 = pixels1[y1 * surface->w + x1];
            Uint32 pixel2 = pixels2[y2 * other->surface->w + x2];
            Uint8 alpha1 = (pixel1 >> 24) & 0xFF;
            Uint8 alpha2 = (pixel2 >> 24) & 0xFF;
            if (alpha1 > 0 && alpha2 > 0)
            {
                return true;
            }
        }
    }
    return false;
}