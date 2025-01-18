#include "Bird.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

template <typename T>
T clamp(T value, T min, T max)
{
    return std::min(std::max(value, min), max);
}

Bird::Bird(SDL_Renderer *ren, int x, int y)
    : AnimatedSprite(ren, "resources/images/bird-wing-up.png", x, y, BIRD_WIDTH, BIRD_HEIGHT),
      flapForce(FLAP_FORCE),
      isDead(false),
      flapSound(nullptr),
      hitSound(nullptr),
      rotation(0),
      targetRotation(0),
      rotationSpeed(300.0f),
      downwardRotationSpeed(100.0f),
      isGameStarted(false),
      initialY(y),
      hoverOffset(0),
      hoverSpeed(2.0f)
{

    flapSound = Mix_LoadWAV("resources/sounds/flap.wav");
    hitSound = Mix_LoadWAV("resources/sounds/hit.wav");
    SDL_Surface *midwaySurface = IMG_Load("resources/images/bird-wing-midway.png");
    SDL_Surface *downSurface = IMG_Load("resources/images/bird-wing-down.png");

    if (midwaySurface && downSurface)
    {
        SDL_Texture *midwayTexture = SDL_CreateTextureFromSurface(ren, midwaySurface);
        SDL_Texture *downTexture = SDL_CreateTextureFromSurface(ren, downSurface);
        frameTextures.push_back(texture);
        frameTextures.push_back(midwayTexture);
        frameTextures.push_back(downTexture);
        frameTextures.push_back(midwayTexture);
        SDL_FreeSurface(midwaySurface);
        SDL_FreeSurface(downSurface);
        SDL_Rect frameRect = {0, 0, BIRD_WIDTH, BIRD_HEIGHT};
        for (int i = 0; i < 4; i++)
        {
            addFrame(frameRect);
        }
    }

    setFrameTime(0.1f);
    setLooping(true);
    setGravityScale(1.0f);
    setElasticity(0.0f);
    velocityY = 0;
    collisionType = CollisionType::PIXEL;
}

Bird::~Bird()
{
    if (flapSound)
        Mix_FreeChunk(flapSound);
    if (hitSound)
        Mix_FreeChunk(hitSound);
    for (size_t i = 1; i < frameTextures.size(); ++i)
    {
        if (frameTextures[i])
        {
            SDL_DestroyTexture(frameTextures[i]);
        }
    }
}

void Bird::update(float deltaTime, bool gameStarted)
{
    if (isDead)
        return;
    AnimatedSprite::update(deltaTime);
    if (!gameStarted)
    {
        hoverOffset += hoverSpeed * deltaTime;
        rect.y = initialY + sin(hoverOffset) * 10.0f;
        rotation = 0;
    }
    else
    {
        PhysicsSprite::update(deltaTime);
        if (velocityY < 0)
        {
            targetRotation = -30.0f;
            float rotationDiff = targetRotation - rotation;
            if (abs(rotationDiff) > 0.1f)
            {
                float rotationChange = rotationSpeed * deltaTime;
                rotation += std::clamp(rotationDiff, -rotationChange, rotationChange);
            }
        }
        else
        {
            targetRotation = 90.0f;
            float rotationDiff = targetRotation - rotation;
            if (abs(rotationDiff) > 0.1f)
            {
                float rotationChange = downwardRotationSpeed * deltaTime;
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

void Bird::startGame()
{
    isGameStarted = true;
    initialY = rect.y;
    velocityY = 0;
}

void Bird::render(SDL_Renderer *ren)
{
    if (!isActive)
        return;
    SDL_Texture *currentTexture = frameTextures[currentFrame];
    if (!currentTexture)
        return;
    SDL_Rect destRect = rect;
    SDL_Point center = {rect.w / 2, rect.h / 2};
    SDL_RenderCopyEx(ren, currentTexture, nullptr, &destRect, rotation, &center, SDL_FLIP_NONE);
}

void Bird::die()
{
    if (!isDead)
    {
        isDead = true;
        if (hitSound)
            Mix_PlayChannel(-1, hitSound, 0);
    }
}

void Bird::handleCollision(Sprite *other)
{
    die();
}
void Bird::flap()
{
    if (!isDead)
    {
        velocityY = -400.0f;
        if (flapSound)
            Mix_PlayChannel(-1, flapSound, 0);
        rotation = -20.0f;
        targetRotation = -30.0f;
    }
}