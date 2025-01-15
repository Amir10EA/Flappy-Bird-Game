// #include <SDL2/SDL.h>
// #include <iostream>
// #include <vector>
// #include <cstdlib> // For rand()
// #include <ctime>   // For srand()

// using namespace std;

// const int WINDOW_WIDTH = 600; 
// const int WINDOW_HEIGHT = 500;
// const int CELL_SIZE = 20;    

// struct SnakeSegment {
//     int x, y;
// };

// struct Food {
//     int x, y;
// };

// void generateFood(Food &food) {
//     food.x = rand() % (WINDOW_WIDTH / CELL_SIZE - 2) + 1; // Avoid the walls
//     food.y = rand() % (WINDOW_HEIGHT / CELL_SIZE - 2) + 1; // Avoid the walls
// }

// int main(int argc, char* argv[]) {

//     if (SDL_Init(SDL_INIT_VIDEO) == -1) {
//         cerr << "SDL_Init error: " << SDL_GetError() << endl; exit(-1);
//     }

//     SDL_Window* win = SDL_CreateWindow("Snake Game",
//         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
//     if (win == nullptr) {
//         cerr << "Window creation error: " << SDL_GetError() << endl; SDL_Quit(); exit(-1);
//     }

//     SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
//     if (ren == nullptr) {
//         cerr << "Renderer creation error: " << SDL_GetError() << endl;
//         SDL_DestroyWindow(win); SDL_Quit(); exit(-1);
//     }

//     srand(time(0)); // Initialize random seed
//     vector<SnakeSegment> snake = {{WINDOW_WIDTH / (2 * CELL_SIZE), WINDOW_HEIGHT / (2 * CELL_SIZE)}};
//     int dx = 0, dy = 0; // Initial direction (no movement)
//     int nextDx = 0, nextDy = 0; // Next movement direction based on user input

//     Food food;
//     generateFood(food); // Generate the first food position

//     bool runOn = true;
//     while (runOn) {
//         SDL_Event eve;
//         while (SDL_PollEvent(&eve)) {
//             switch (eve.type) {
//                 case SDL_QUIT:
//                     runOn = false;
//                     break;
//                 case SDL_KEYDOWN:
//                     // Prevent immediate reversal of direction
//                     switch (eve.key.keysym.sym) {
//                         case SDLK_UP:    
//                             if (dy == 0) { nextDx = 0; nextDy = -1; } 
//                             break;
//                         case SDLK_DOWN:  
//                             if (dy == 0) { nextDx = 0; nextDy = 1; } 
//                             break;
//                         case SDLK_LEFT:  
//                             if (dx == 0) { nextDx = -1; nextDy = 0; } 
//                             break;
//                         case SDLK_RIGHT: 
//                             if (dx == 0) { nextDx = 1; nextDy = 0; } 
//                             break;
//                         case SDLK_END:
//                             runOn = false;
//                             break;
//                     }
//                     break;
//             }
//         }

//         // Update snake's direction only if the next direction is valid
//         if (nextDx != 0 || nextDy != 0) {
//             dx = nextDx;
//             dy = nextDy;
//         }

//         // Check for collision with walls BEFORE moving
//         if (snake[0].x <= 0 || snake[0].x >= (WINDOW_WIDTH / CELL_SIZE) - 1 || 
//             snake[0].y <= 0 || snake[0].y >= (WINDOW_HEIGHT / CELL_SIZE) - 1) {
//             cout << "Game Over! Snake hit the wall." << endl;
//             runOn = false; // End the game if the snake hits the wall
//             continue; // Skip the movement and rendering logic
//         }

//         // Move the snake's body
//         for (int i = snake.size() - 1; i > 0; --i) {
//             snake[i] = snake[i - 1]; 
//         }
//         snake[0].x += dx;
//         snake[0].y += dy;

//         // Check if snake ate the food
//         bool ateFood = false;
//         if (snake[0].x == food.x && snake[0].y == food.y) {
//             snake.push_back(snake.back()); // Add a new segment to the tail
//             generateFood(food); // Generate a new food position
//             ateFood = true;
//         }

//         // Check if snake hit its own body (after moving)
//         if (!ateFood) {
//             for (int i = 1; i < snake.size(); ++i) {
//                 if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
//                     cout << "Game Over! Snake hit itself." << endl;
//                     runOn = false;
//                     break;
//                 }
//             }
//         }

//         SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
//         SDL_RenderClear(ren);

//         // Draw grid and walls
//         for (int y = 0; y < WINDOW_HEIGHT / CELL_SIZE; ++y) {
//             for (int x = 0; x < WINDOW_WIDTH / CELL_SIZE; ++x) {
//                 if (x == 0 || y == 0 || x == (WINDOW_WIDTH / CELL_SIZE) - 1 || y == (WINDOW_HEIGHT / CELL_SIZE) - 1) {
//                     SDL_SetRenderDrawColor(ren, 205, 133, 63, 255); // Light brown (walls)
//                 } else if ((x + y) % 2 == 0) {
//                     SDL_SetRenderDrawColor(ren, 173, 255, 173, 255); // Lighter green
//                 } else {
//                     SDL_SetRenderDrawColor(ren, 144, 238, 144, 255); // Light green
//                 }
//                 SDL_Rect rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
//                 SDL_RenderFillRect(ren, &rect);
//             }
//         }

//         // Draw snake
//         SDL_SetRenderDrawColor(ren, 128, 0, 128, 255); // Purple
//         for (const auto& segment : snake) {
//             SDL_Rect rect = {segment.x * CELL_SIZE, segment.y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
//             SDL_RenderFillRect(ren, &rect);
//         }

//         // Draw food
//         SDL_SetRenderDrawColor(ren, 255, 0, 0, 255); // Red
//         SDL_Rect foodRect = {food.x * CELL_SIZE, food.y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
//         SDL_RenderFillRect(ren, &foodRect);

//         SDL_RenderPresent(ren);
//         SDL_Delay(100); 
//     }

//     SDL_DestroyRenderer(ren);
//     SDL_DestroyWindow(win);
//     SDL_Quit();
//     return 0;
// }
