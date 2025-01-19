#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(SDL_Renderer *renderer, TTF_Font *font)
    : font(font),
      scoretexture(nullptr),
      bestscoretexture(nullptr),
      restarttexture(nullptr),
      curentscore(0),
      bestscore(0)
{
    int panelHeight = 400;
    int panelTop = WINDOW_HEIGHT / 2 - panelHeight / 2;
    gameoverRect = {
        WINDOW_WIDTH / 2 - 150,
        panelTop + 40,
        300,
        60};
    scoreRect = {
        WINDOW_WIDTH / 2 - 100,
        gameoverRect.y + gameoverRect.h + 30,
        200,
        50};
    bestscoreRect = {
        WINDOW_WIDTH / 2 - 100,
        scoreRect.y + scoreRect.h + 20,
        200,
        50};
    buttonRect = {
        WINDOW_WIDTH / 2 - 100,
        bestscoreRect.y + bestscoreRect.h + 25,
        200,
        60};
}
GameOverScreen::~GameOverScreen()
{
    if (scoretexture)
        SDL_DestroyTexture(scoretexture);
    if (bestscoretexture)
        SDL_DestroyTexture(bestscoretexture);
    if (restarttexture)
        SDL_DestroyTexture(restarttexture);
}
void GameOverScreen::update(int score)
{
    curentscore = score;
    if (score > bestscore)
    {
        bestscore = score;
    }
}
void GameOverScreen::setBestScore(int score)
{
    bestscore = score;
}
void GameOverScreen::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_Rect fullscreen = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer, &fullscreen);
    SDL_Rect panel = {
        WINDOW_WIDTH / 2 - 200,
        WINDOW_HEIGHT / 2 - 200,
        400,
        400};
    SDL_SetRenderDrawColor(renderer, 45, 45, 48, 255);
    SDL_RenderFillRect(renderer, &panel);
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
    SDL_RenderDrawRect(renderer, &panel);
    SDL_Color titleColour = {255, 215, 0, 255};
    SDL_Color highlightColour = {0, 255, 255, 255};
    SDL_Rect shadowRect = gameoverRect;
    shadowRect.x += 2;
    shadowRect.y += 2;
    SDL_Color shadowColor = {0, 0, 0, 255};
    renderText(renderer, "Game Over!", shadowRect, shadowColor);
    renderText(renderer, "Game Over!", gameoverRect, titleColour);
    std::string scoreStr = "Score:" + std::to_string(curentscore);
    std::string bestStr = "Best:" + std::to_string(bestscore);
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), highlightColour);
    if (scoreSurface)
    {
        SDL_Rect centeredscoreRect = scoreRect;
        centeredscoreRect.w = scoreSurface->w;
        centeredscoreRect.h = scoreSurface->h;
        centeredscoreRect.x = WINDOW_WIDTH / 2 - scoreSurface->w / 2;

        SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_RenderCopy(renderer, scoreTexture, nullptr, &centeredscoreRect);
        SDL_DestroyTexture(scoreTexture);
        SDL_FreeSurface(scoreSurface);
    }
    SDL_Surface *bestSurface = TTF_RenderText_Solid(font, bestStr.c_str(), highlightColour);
    if (bestSurface)
    {
        SDL_Rect centeredBestRect = bestscoreRect;
        centeredBestRect.w = bestSurface->w;
        centeredBestRect.h = bestSurface->h;
        centeredBestRect.x = WINDOW_WIDTH / 2 - bestSurface->w / 2;
        SDL_Texture *bestTexture = SDL_CreateTextureFromSurface(renderer, bestSurface);
        SDL_RenderCopy(renderer, bestTexture, nullptr, &centeredBestRect);
        SDL_DestroyTexture(bestTexture);
        SDL_FreeSurface(bestSurface);
    }
    SDL_Rect paddedButton = buttonRect;
    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 255);
    SDL_RenderFillRect(renderer, &paddedButton);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 40);
    SDL_RenderDrawRect(renderer, &paddedButton);
    SDL_Rect textRect = {
        paddedButton.x + 20,
        paddedButton.y + 15,
        paddedButton.w - 40,
        paddedButton.h - 30};
    SDL_Color buttonTextColor = {255, 255, 255, 255};
    renderText(renderer, "Restart", textRect, buttonTextColor);
}

void GameOverScreen::renderText(SDL_Renderer *renderer, const std::string &text, SDL_Rect &rect, SDL_Color &colour)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), colour);
    if (surface)
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
}

bool GameOverScreen::isRestartButtonClicked(int xcor, int ycor) const
{
    return (xcor >= buttonRect.x && xcor <= buttonRect.x + buttonRect.w &&
            ycor >= buttonRect.y && ycor <= buttonRect.y + buttonRect.h);
}