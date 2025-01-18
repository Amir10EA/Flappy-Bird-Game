#include "GameLevel.h"
#include <algorithm>
#include <iostream>
using namespace std;

GameLevel::GameLevel(SDL_Renderer *ren)
    : score(0),
      bestScore(0),
      difficulty(1.0f),
      currentLevel(1),
      levelUpThreshold(10),
      renderer(ren),
      backgroundOffset(0),
      gameStarted(false),
      levelUpSound(nullptr)
{
    levelUpSound = Mix_LoadWAV("resources/sounds/level-up.wav");
    if (!levelUpSound)
    {
        std::cerr << "Failed to load level up sound: " << Mix_GetError() << std::endl;
    }

    SDL_Surface *bgSurface = IMG_Load("resources/images/flappy-bird-background.jpg");
    if (bgSurface)
    {
        backgroundTexture = SDL_CreateTextureFromSurface(ren, bgSurface);
        SDL_FreeSurface(bgSurface);
    }
    else
    {
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
        backgroundTexture = nullptr;
    }
    bird = new Bird(ren, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
    sprites.push_back(std::unique_ptr<Sprite>(bird));
    for (int i = 0; i < 3; ++i)
    {
        int x = WINDOW_WIDTH + (i * PIPE_SPACING);
        Pipe *topPipe = new Pipe(ren, "resources/images/pipe.png", x, 0, true);
        Pipe *bottomPipe = new Pipe(ren, "resources/images/pipe.png", x, 0, false);
        pipes.push_back(topPipe);
        pipes.push_back(bottomPipe);
        sprites.push_back(std::unique_ptr<Sprite>(topPipe));
        sprites.push_back(std::unique_ptr<Sprite>(bottomPipe));
    }
    font = TTF_OpenFont("resources/fonts/PressStart2P.ttf", 28);
    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }
    scoreTexture = nullptr;
    levelTexture = nullptr;
    gameOverScreen = std::make_unique<GameOverScreen>(ren, font);
    updateScoreTexture(renderer);
    updateLevelTexture(renderer);
    loadBestScore();
}

GameLevel::~GameLevel()
{
    if (levelUpSound)
    {
        Mix_FreeChunk(levelUpSound);
    }
    if (backgroundTexture)
    {
        SDL_DestroyTexture(backgroundTexture);
    }
    if (scoreTexture)
    {
        SDL_DestroyTexture(scoreTexture);
    }
    if (font)
    {
        TTF_CloseFont(font);
    }
}

void GameLevel::update(float deltaTime)
{
    if (!bird->isDying())
    {
        if (gameStarted)
        {
            backgroundOffset += BACKGROUND_SCROLL_SPEED;
            if (backgroundOffset >= 767)
            {
                backgroundOffset = 0;
            }
            for (auto &sprite : sprites)
            {
                if (dynamic_cast<Pipe *>(sprite.get()))
                {
                    sprite->update(deltaTime);
                }
            }
            for (auto &sprite : sprites)
            {
                if (sprite.get() != bird && bird->checkCollision(sprite.get()))
                {
                    bird->handleCollision(sprite.get());
                }
            }
            for (size_t i = 0; i < pipes.size(); i += 2)
            {
                float pipeRightEdge = pipes[i]->getRect().x + PIPE_WIDTH;
                float birdCenterX = bird->getRect().x + (bird->getRect().w / 2);
                if (pipeRightEdge <= birdCenterX &&
                    pipeRightEdge > birdCenterX - (INITIAL_SCROLL_SPEED * difficulty))
                {
                    score++;
                    updateScoreTexture(renderer);
                    int newLevel = (score / static_cast<int>(levelUpThreshold)) + 1;
                    if (newLevel != currentLevel)
                    {
                        currentLevel = newLevel;
                        difficulty = 1.0f + (currentLevel - 1) * 0.2f;
                        updateLevelTexture(renderer);
                        if (levelUpSound)
                        {
                            Mix_PlayChannel(-1, levelUpSound, 0);
                        }
                        for (auto pipe : pipes)
                        {
                            pipe->setScrollSpeed(INITIAL_SCROLL_SPEED * difficulty);
                        }
                    }
                }
            }
        }
        bird->update(deltaTime, gameStarted);
    }
    else
    {
        saveBestScore();
    }
}

void GameLevel::render(SDL_Renderer *ren)
{
    if (backgroundTexture)
    {
        SDL_Rect srcRect = {
            static_cast<int>(backgroundOffset), 0,
            WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_Rect destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderCopy(ren, backgroundTexture, &srcRect, &destRect);
    }
    for (auto &sprite : sprites)
    {
        sprite->render(ren);
    }
    SDL_Rect panelRect = {
        (WINDOW_WIDTH - 240) / 2, 15, 240, 120};

    if (levelTexture)
    {
        SDL_Rect levelRect = {
            panelRect.x + (panelRect.w - 150) / 2,
            panelRect.y + 15,
            150,
            40};
        SDL_RenderCopy(ren, levelTexture, nullptr, &levelRect);
    }

    if (scoreTexture)
    {
        SDL_Rect scoreRect = {
            panelRect.x + (panelRect.w - 130) / 2,
            panelRect.y + 65,
            130,
            40};
        SDL_RenderCopy(ren, scoreTexture, nullptr, &scoreRect);
    }

    if (bird->isDying())
    {
        gameOverScreen->update(score);
        gameOverScreen->render(ren);
    }
}
void GameLevel::handleInput(const SDL_Event &event)
{
    if (bird->isDying())
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (gameOverScreen->isRestartButtonClicked(mouseX, mouseY))
            {
                reset();
            }
        }
    }
    else
    {
        if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||
            (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))
        {
            if (!gameStarted)
            {
                gameStarted = true;
                bird->startGame();
            }
            bird->flap();
        }
    }
}

void GameLevel::loadBestScore()
{
    std::ifstream file("best_score.dat");
    if (file.is_open())
    {
        file >> bestScore;
        file.close();
    }
    else
    {
        bestScore = 0;
    }
    if (gameOverScreen)
    {
        gameOverScreen->setBestScore(bestScore);
    }
}

void GameLevel::saveBestScore()
{
    if (score > bestScore)
    {
        bestScore = score;
        std::ofstream file("best_score.dat");
        if (file.is_open())
        {
            file << bestScore;
            file.close();
        }
        if (gameOverScreen)
        {
            gameOverScreen->setBestScore(bestScore);
        }
    }
}

void GameLevel::reset()
{
    score = 0;
    currentLevel = 1;
    difficulty = 1.0f;
    gameStarted = false;
    bird->setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
    bird->setVelocity(0, 0);
    bird->resetState();
    for (size_t i = 0; i < pipes.size(); i += 2)
    {
        float spacing = (i / 2) * PIPE_SPACING;
        pipes[i]->reset(WINDOW_WIDTH + spacing);
        pipes[i + 1]->reset(WINDOW_WIDTH + spacing);
        pipes[i]->setScrollSpeed(INITIAL_SCROLL_SPEED);
        pipes[i + 1]->setScrollSpeed(INITIAL_SCROLL_SPEED);
    }
    updateScoreTexture(renderer);
    updateLevelTexture(renderer);
}

void GameLevel::updateScoreTexture(SDL_Renderer *ren)
{
    if (scoreTexture)
    {
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = nullptr;
    }
    SDL_Color textColor = {255, 255, 255, 255};
    std::string scoreText = "   " + std::to_string(score) + "   ";
    SDL_Surface *surface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (!surface)
    {
        printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        return;
    }
    scoreTexture = SDL_CreateTextureFromSurface(ren, surface);
    if (!scoreTexture)
    {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    SDL_FreeSurface(surface);
}

void GameLevel::updateLevelTexture(SDL_Renderer *ren)
{
    if (levelTexture)
    {
        SDL_DestroyTexture(levelTexture);
    }
    SDL_Color color = {255, 215, 0, 255};
    std::string levelText = "Level " + std::to_string(currentLevel);
    SDL_Surface *surface = TTF_RenderText_Solid(font, levelText.c_str(), color);
    if (surface)
    {
        levelTexture = SDL_CreateTextureFromSurface(ren, surface);
        SDL_FreeSurface(surface);
    }
}