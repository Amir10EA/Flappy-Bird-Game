#include "Bird.h"

template <typename T>
T clamp(T value, T min, T max)
{
    return std::min(std::max(value, min), max);
}

Bird::Bird(SDL_Renderer *ren, int x, int y)
    : AnimatedSprite(ren, "resources/images/bird-wing-up.png", x, y, BIRD_WIDTH, BIRD_HEIGHT),
      flappower(FLAP_FORCE),
      dead(false),
      flaxsound(nullptr),
      hitsound(nullptr),
      rotation(0),
      targetrotation(0),
      speedrotation(300.0f),
      rotationdown(100.0f),
      gamestarted(false),
      initialY(y),
      offset(0),
      hoverspeed(2.0f)
{

    flaxsound = Mix_LoadWAV("resources/sounds/flap.wav");
    hitsound = Mix_LoadWAV("resources/sounds/hit.wav");
    SDL_Surface *midwaySurface = IMG_Load("resources/images/bird-wing-midway.png");
    SDL_Surface *downSurface = IMG_Load("resources/images/bird-wing-down.png");

    if (midwaySurface && downSurface)
    {
        SDL_Texture *midwayTexture = SDL_CreateTextureFromSurface(ren, midwaySurface);
        SDL_Texture *downTexture = SDL_CreateTextureFromSurface(ren, downSurface);
        textures.push_back(texture);
        textures.push_back(midwayTexture);
        textures.push_back(downTexture);
        textures.push_back(midwayTexture);
        SDL_FreeSurface(midwaySurface);
        SDL_FreeSurface(downSurface);
        SDL_Rect frameRect = {0, 0, BIRD_WIDTH, BIRD_HEIGHT};
        for (int i = 0; i < 4; i++)
        {
            addframe(frameRect);
        }
    }

    settimeframe(0.1f);
    setlooping(true);
    setGravityScale(1.0f);
    setElasticity(0.0f);
    velocityY = 0;
    collisionType = CollisionType::PIXEL;
}

Bird::~Bird()
{
    if (flaxsound)
        Mix_FreeChunk(flaxsound);
    if (hitsound)
        Mix_FreeChunk(hitsound);
    for (size_t i = 1; i < textures.size(); ++i)
    {
        if (textures[i])
        {
            SDL_DestroyTexture(textures[i]);
        }
    }
}

void Bird::update(float time, bool gameStarted)
{
    if (dead)
        return;
    AnimatedSprite::update(time);
    if (!gameStarted)
    {
        offset += hoverspeed * time;
        rect.y = initialY + sin(offset) * 10.0f;
        rotation = 0;
    }
    else
    {
        PhysicsSprite::update(time);
        if (velocityY < 0)
        {
            targetrotation = -30.0f;
            float rotationdifference = targetrotation - rotation;
            if (abs(rotationdifference) > 0.1f)
            {
                float rotationChange = speedrotation * time;
                rotation += std::clamp(rotationdifference, -rotationChange, rotationChange);
            }
        }
        else
        {
            targetrotation = 90.0f;
            float rotationDiff = targetrotation - rotation;
            if (abs(rotationDiff) > 0.1f)
            {
                float rotationChange = rotationdown * time;
                rotation += std::clamp(rotationDiff, -rotationChange, rotationChange);
            }
        }
        rotation = std::clamp(rotation, -30.0f, 90.0f);
        if (rect.y < 0)
        {
            rect.y = 0;
            velocityY = 0;
            die();
        }
        if (rect.y + rect.h > WINDOW_HEIGHT - GROUND_HEIGHT)
        {
            rect.y = WINDOW_HEIGHT - GROUND_HEIGHT - rect.h;
            velocityY = 0;
            die();
        }
    }
}

void Bird::reset(){
         dead = false;
        velocityY = 0;
}
void Bird::startGame()
{
    gamestarted = true;
    initialY = rect.y;
    velocityY = 0;
}

void Bird::render(SDL_Renderer *renderer)
{
    if (!isActive)
        return;
    SDL_Texture *currentTexture = textures[curentframe];
    if (!currentTexture)
        return;
    SDL_Rect destRect = rect;
    SDL_Point center = {rect.w / 2, rect.h / 2};
    SDL_RenderCopyEx(renderer, currentTexture, nullptr, &destRect, rotation, &center, SDL_FLIP_NONE);
}

void Bird::die()
{
    if (!dead)
    {
        dead = true;
        if (hitsound)
            Mix_PlayChannel(-1, hitsound, 0);
    }
}

void Bird::handleCollision(Sprite *other)
{
    die();
}
void Bird::flap()
{
    if (!dead)
    {
        velocityY = -400.0f;
        if (flaxsound)
            Mix_PlayChannel(-1, flaxsound, 0);
        rotation = -20.0f;
        targetrotation = -30.0f;
    }
}