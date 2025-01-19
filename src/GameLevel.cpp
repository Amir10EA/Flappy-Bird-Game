#include "GameLevel.h"
#include <algorithm>
#include <iostream>
using namespace std;

GameLevel::GameLevel(SDL_Renderer *renderer)
    : score(0),
      bestScore(0),
      difficulty(1.0f),
      curentlevel(1),
      levelupthreshold(10),
      renderer(renderer),
      backgroundoffset(0),
      started(false),
      levelupsound(nullptr)
{
    levelupsound = Mix_LoadWAV("resources/sounds/level-up.wav");
    if (!levelupsound)
    {
        std::cerr << Mix_GetError() << std::endl;
    }

    SDL_Surface *bgSurface = IMG_Load("resources/images/flappy-bird-background.jpg");
    if (bgSurface)
    {
        backgroundtexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);
    }
    else
    {
        std::cerr << IMG_GetError() << std::endl;
        backgroundtexture = nullptr;
    }
    bird = new Bird(renderer, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
    sprites.push_back(std::unique_ptr<Sprite>(bird));
    for (int i = 0; i < 3; ++i)
    {
        int x = WINDOW_WIDTH + (i * PIPE_SPACING);
        Pipe *topPipe = new Pipe(renderer, "resources/images/pipe.png", x, 0, true);
        Pipe *bottomPipe = new Pipe(renderer, "resources/images/pipe.png", x, 0, false);
        pipes.push_back(topPipe);
        pipes.push_back(bottomPipe);
        sprites.push_back(std::unique_ptr<Sprite>(topPipe));
        sprites.push_back(std::unique_ptr<Sprite>(bottomPipe));
    }
    font = TTF_OpenFont("resources/fonts/PressStart2P.ttf", 28);
    if (!font)
    {
        std::cerr << TTF_GetError() << std::endl;
        return;
    }
    scoretexture = nullptr;
    leveltexture = nullptr;
    gameoverscreen = std::make_unique<GameOverScreen>(renderer, font);
    updateScoreTexture(renderer);
    updateLevelTexture(renderer);
    loadBestScore();
}

GameLevel::~GameLevel()
{
    if (levelupsound)
    {
        Mix_FreeChunk(levelupsound);
    }
    if (backgroundtexture)
    {
        SDL_DestroyTexture(backgroundtexture);
    }
    if (scoretexture)
    {
        SDL_DestroyTexture(scoretexture);
    }
    if (font)
    {
        TTF_CloseFont(font);
    }
}

void GameLevel::update(float time)
{
    if (!bird->isDying())
    {
        if (started)
        {
            backgroundoffset += BACKGROUND_SCROLL_SPEED;
            if (backgroundoffset >= 767)
            {
                backgroundoffset = 0;
            }
            for (auto &sprite : sprites)
            {
                if (dynamic_cast<Pipe *>(sprite.get()))
                {
                    sprite->update(time);
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
                float rightedge = pipes[i]->getRect().x + PIPE_WIDTH;
                float centerofbird = bird->getRect().x + (bird->getRect().w / 2);
                if (rightedge <= centerofbird &&
                    rightedge > centerofbird - (INITIAL_SCROLL_SPEED * difficulty))
                {
                    score++;
                    updateScoreTexture(renderer);
                    int newlevel = (score / static_cast<int>(levelupthreshold)) + 1;
                    if (newlevel != curentlevel)
                    {
                        curentlevel = newlevel;
                        difficulty = 1.0f + (curentlevel - 1) * 0.2f;
                        updateLevelTexture(renderer);
                        if (levelupsound)
                        {
                            Mix_PlayChannel(-1, levelupsound, 0);
                        }
                        for (auto pipe : pipes)
                        {
                            pipe->setScrollSpeed(INITIAL_SCROLL_SPEED * difficulty);
                        }
                    }
                }
            }
        }
        bird->update(time, started);
    }
    else
    {
        saveBestScore();
    }
}

void GameLevel::render(SDL_Renderer *renderer)
{
    if (backgroundtexture)
    {
        SDL_Rect srcRect = {
            static_cast<int>(backgroundoffset), 0,
            WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_Rect destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderCopy(renderer, backgroundtexture, &srcRect, &destRect);
    }
    for (auto &sprite : sprites)
    {
        sprite->render(renderer);
    }
    SDL_Rect panelRect = {
        (WINDOW_WIDTH - 240) / 2, 15, 240, 120};

    if (leveltexture)
    {
        SDL_Rect levelRect = {
            panelRect.x + (panelRect.w - 150) / 2,
            panelRect.y + 15,
            150,
            40};
        SDL_RenderCopy(renderer, leveltexture, nullptr, &levelRect);
    }

    if (scoretexture)
    {
        SDL_Rect scoreRect = {
            panelRect.x + (panelRect.w - 130) / 2,
            panelRect.y + 65,
            130,
            40};
        SDL_RenderCopy(renderer, scoretexture, nullptr, &scoreRect);
    }

    if (bird->isDying())
    {
        gameoverscreen->update(score);
        gameoverscreen->render(renderer);
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
            if (gameoverscreen->isRestartButtonClicked(mouseX, mouseY))
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
            if (!started)
            {
                started = true;
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
    if (gameoverscreen)
    {
        gameoverscreen->setBestScore(bestScore);
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
        if (gameoverscreen)
        {
            gameoverscreen->setBestScore(bestScore);
        }
    }
}

void GameLevel::reset()
{
    score = 0;
    curentlevel = 1;
    difficulty = 1.0f;
    started = false;
    bird->setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
    bird->setVelocity(0, 0);
    bird->reset();
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
    if (scoretexture)
    {
        SDL_DestroyTexture(scoretexture);
        scoretexture = nullptr;
    }
    SDL_Color textColor = {255, 255, 255, 255};
    std::string scoreText = "   " + std::to_string(score) + "   ";
    SDL_Surface *surface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (!surface)
    {
        printf("%s\n", TTF_GetError());
        return;
    }
    scoretexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!scoretexture)
    {
        printf("%s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    SDL_FreeSurface(surface);
}

void GameLevel::updateLevelTexture(SDL_Renderer *renderer)
{
    if (leveltexture)
    {
        SDL_DestroyTexture(leveltexture);
    }
    SDL_Color colour = {255, 215, 0, 255};
    std::string levelText = "Level " + std::to_string(curentlevel);
    SDL_Surface *surface = TTF_RenderText_Solid(font, levelText.c_str(), colour);
    if (surface)
    {
        leveltexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}