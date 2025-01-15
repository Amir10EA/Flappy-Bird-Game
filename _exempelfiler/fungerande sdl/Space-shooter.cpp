// #include <SDL2/SDL.h>
// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// // Path to the images (you can change these)
// string bgPath = "C:/Users/amire/Downloads/cprog_template_win_241106/resources/images/bg2.bmp";
// string playerPath = "D:/random files/random images/download_jpeg.bmp"; // Player image
// string bulletPath = "D:/random files/random images/download_jpeg.bmp"; // Bullet image

// // Define the player and bullet movement speed
// const int playerSpeed = 10;
// const int bulletSpeed = 10;

// // Player class
// class Player {
// public:
//     SDL_Rect rect;
//     SDL_Texture* texture;

//     Player(SDL_Renderer* renderer) {
//         SDL_Surface* surface = SDL_LoadBMP(playerPath.c_str());
//         texture = SDL_CreateTextureFromSurface(renderer, surface);
//         SDL_FreeSurface(surface);
//         rect = { 300, 400, 50, 50 }; // Starting position of the player
//     }

//     void move(SDL_Event& event) {
//         if (event.type == SDL_KEYDOWN) {
//             switch (event.key.keysym.sym) {
//                 case SDLK_LEFT: rect.x -= playerSpeed; break;
//                 case SDLK_RIGHT: rect.x += playerSpeed; break;
//                 case SDLK_UP: rect.y -= playerSpeed; break;
//                 case SDLK_DOWN: rect.y += playerSpeed; break;
//             }
//         }
//     }

//     void draw(SDL_Renderer* renderer) {
//         SDL_RenderCopy(renderer, texture, NULL, &rect);
//     }
// };

// // Bullet class
// class Bullet {
// public:
//     SDL_Rect rect;
//     SDL_Texture* texture;

//     Bullet(SDL_Renderer* renderer, int startX, int startY) {
//         SDL_Surface* surface = SDL_LoadBMP(bulletPath.c_str());
//         texture = SDL_CreateTextureFromSurface(renderer, surface);
//         SDL_FreeSurface(surface);
//         rect = { startX, startY, 10, 20 }; // Bullet size and position
//     }

//     void move() {
//         rect.y -= bulletSpeed; // Move the bullet upwards
//     }

//     void draw(SDL_Renderer* renderer) {
//         SDL_RenderCopy(renderer, texture, NULL, &rect);
//     }
// };

// // Main game function
// int main(int argc, char* argv[]) {
//     if (SDL_Init(SDL_INIT_VIDEO) == -1) {
//         cerr << "SDL_Init error: " << SDL_GetError() << endl;
//         exit(-1);
//     }

//     SDL_Window* win = SDL_CreateWindow("Shooter Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 500, SDL_WINDOW_SHOWN);
//     if (win == nullptr) {
//         cerr << "Window creation error: " << SDL_GetError() << endl;
//         SDL_Quit();
//         exit(-1);
//     }

//     SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
//     if (ren == nullptr) {
//         cerr << "Renderer creation error: " << SDL_GetError() << endl;
//         SDL_DestroyWindow(win);
//         SDL_Quit();
//         exit(-1);
//     }

//     SDL_Surface* bgSurf = SDL_LoadBMP(bgPath.c_str());
//     SDL_Texture* bgTx = SDL_CreateTextureFromSurface(ren, bgSurf);
//     SDL_FreeSurface(bgSurf);

//     Player player(ren);
//     vector<Bullet> bullets;
//     bool runOn = true;

//     while (runOn) {
//         SDL_Event eve;
//         while (SDL_PollEvent(&eve)) {
//             if (eve.type == SDL_QUIT) {
//                 runOn = false;
//             }

//             // Player movement
//             player.move(eve);

//             // Shooting (spacebar)
//             if (eve.type == SDL_KEYDOWN && eve.key.keysym.sym == SDLK_SPACE) {
//                 bullets.push_back(Bullet(ren, player.rect.x + player.rect.w / 2 - 5, player.rect.y)); // Create bullet at player's position
//             }
//         }

//         // Move the bullets
//         for (auto& bullet : bullets) {
//             bullet.move();
//         }

//         // Remove bullets that go off the screen
//         bullets.erase(remove_if(bullets.begin(), bullets.end(), [](Bullet& b) {
//             return b.rect.y < 0;
//         }), bullets.end());

//         // Render everything
//         SDL_RenderClear(ren);
//         SDL_RenderCopy(ren, bgTx, NULL, NULL); // Draw the background
//         player.draw(ren); // Draw the player

//         // Draw bullets
//         for (auto& bullet : bullets) {
//             bullet.draw(ren);
//         }

//         SDL_RenderPresent(ren); // Update screen
//         SDL_Delay(16); // Frame rate control (about 60 FPS)
//     }

//     // Cleanup
//     SDL_DestroyTexture(bgTx);
//     SDL_DestroyRenderer(ren);
//     SDL_DestroyWindow(win);
//     SDL_Quit();
//     return 0;
// }
