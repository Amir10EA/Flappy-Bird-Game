#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

using namespace std;

const int WINDOW_WIDTH = 600; 
const int WINDOW_HEIGHT = 500;
const int CELL_SIZE = 20;    

struct SnakeSegment {
    int x, y;
};

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        cerr << "SDL_Init error: " << SDL_GetError() << endl; exit(-1);
    }

    SDL_Window* win = SDL_CreateWindow("Snake Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        cerr << "Window creation error: " << SDL_GetError() << endl; SDL_Quit(); exit(-1);
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        cerr << "Renderer creation error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(win); SDL_Quit(); exit(-1);
    }

 
    vector<SnakeSegment> snake = {{WINDOW_WIDTH / (2 * CELL_SIZE), WINDOW_HEIGHT / (2 * CELL_SIZE)}};
    int dx = 0, dy = 0; 

    bool runOn = true;
    while (runOn) {
        SDL_Event eve;
        while (SDL_PollEvent(&eve)) {
            switch (eve.type) {
                case SDL_QUIT:
                    runOn = false;
                    break;
                case SDL_KEYDOWN:
                    switch (eve.key.keysym.sym) {
                        case SDLK_UP:    dx = 0; dy = -1; break;
                        case SDLK_DOWN:  dx = 0; dy = 1; break;
                        case SDLK_LEFT:  dx = -1; dy = 0; break;
                        case SDLK_RIGHT: dx = 1; dy = 0; break;
                        case SDLK_END:
                            runOn = false;
                            break;
                    }
                    break;
            }
        }


        for (int i = snake.size() - 1; i > 0; --i) {
            snake[i] = snake[i - 1]; 
        }
        snake[0].x += dx;
        snake[0].y += dy;

 
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

 
        SDL_SetRenderDrawColor(ren, 50, 50, 50, 255);
        for (int i = 0; i <= WINDOW_WIDTH; i += CELL_SIZE) {
            SDL_RenderDrawLine(ren, i, 0, i, WINDOW_HEIGHT);
        }
        for (int j = 0; j <= WINDOW_HEIGHT; j += CELL_SIZE) {
            SDL_RenderDrawLine(ren, 0, j, WINDOW_WIDTH, j);
        }

     
        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
        for (const auto& segment : snake) {
            SDL_Rect rect = {segment.x * CELL_SIZE, segment.y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_RenderFillRect(ren, &rect);
        }

        SDL_RenderPresent(ren);
        SDL_Delay(100); 
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
