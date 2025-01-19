
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_main.h>
#include "Game.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char *argv[])
{
    SDL_SetMainReady();
    try
    {
        Game game;
        if (!game.initialize())
        {
            throw std::runtime_error("initialization error");
        }
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}