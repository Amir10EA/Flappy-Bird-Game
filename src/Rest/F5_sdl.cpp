// #include <SDL2/SDL.h> // Inkluderar SDL2-biblioteket för att använda SDL-funktioner
// #include <iostream>   // Inkluderar iostream för att använda std::cerr och std::endl
// #include <string>     // Inkluderar string för att använda std::string

// using namespace std;  // Använder standardnamnrymden för att slippa skriva std:: före varje standardfunktion

// // Definierar sökvägarna till bilderna
// string bgPath = "C:/Users/amire/Downloads/cprog_template_win_241106/resources/images/bg2.bmp";
// string gubbPath = "D:/random files/random images/download_jpeg.bmp";

// int main(int argc, char* argv[]) {
//     // Initierar SDL2-biblioteket för videofunktioner
//     if (SDL_Init(SDL_INIT_VIDEO) == -1) {
//         cerr << "SDL_Init error: " << SDL_GetError() << endl; exit(-1);
//     }

//     // Skapar ett fönster med titeln "Mitt" och storleken 600x500 pixlar
//     SDL_Window* win = SDL_CreateWindow("Mitt",
//         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 500, SDL_WINDOW_SHOWN);
//     if (win == nullptr) {
//         cerr << "Window creation error: " << SDL_GetError() << endl; SDL_Quit(); exit(-1);
//     }

//     // Skapar en renderer som används för att rita i fönstret
//     SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
//     if (ren == nullptr) {
//         cerr << "Renderer creation error: " << SDL_GetError() << endl; SDL_DestroyWindow(win); SDL_Quit(); exit(-1);
//     }

//     // Laddar bakgrundsbilden från filen
//     SDL_Surface* bgSurf = SDL_LoadBMP(bgPath.c_str());
//     // Skapar en textur från bakgrundsbilden
//     SDL_Texture* bgTx = SDL_CreateTextureFromSurface(ren, bgSurf); SDL_FreeSurface(bgSurf);

//     // Laddar gubbbilden från filen
//     SDL_Surface* gubbSurf = SDL_LoadBMP(gubbPath.c_str());
//     // Skapar en rektangel som representerar gubbbildens position och storlek
//     SDL_Rect gubbRect = {0, 0, gubbSurf->w, gubbSurf->h};
//     // Definierar vit färg för att använda som genomskinlig färg
//     Uint32 white = SDL_MapRGB(gubbSurf->format, 255, 255, 255);
//     // Sätter vit färg som genomskinlig i gubbbilden
//     SDL_SetColorKey(gubbSurf, SDL_TRUE, white);
//     // Skapar en textur från gubbbilden
//     SDL_Texture* gubbTx = SDL_CreateTextureFromSurface(ren, gubbSurf); SDL_FreeSurface(gubbSurf);

//     // Variabel för att hålla reda på om programmet ska fortsätta köra
//     bool runOn = true, drag = false;
//     while (runOn) {
//         SDL_Event eve;
//         // Hanterar händelser (t.ex. tangenttryckningar, musrörelser)
//         while (SDL_PollEvent(&eve)) {
//             switch (eve.type) {
//                 case SDL_QUIT:
//                     runOn = false;
//                     break;
//                 case SDL_KEYDOWN:
//                     switch(eve.key.keysym.sym) {
//                         case SDLK_UP:
//                             gubbRect.y-=10;
//                             break;
//                         case SDLK_DOWN:
//                             gubbRect.y+=10;
//                             break;
//                         case SDLK_LEFT:
//                             gubbRect.x-=10;
//                             break;
//                         case SDLK_RIGHT:
//                             gubbRect.x+=10;
//                             break;
//                     }
                    
//                     if (eve.key.keysym.sym == SDLK_END)
//                         runOn = false;
//                     break;
//                 case SDL_MOUSEBUTTONDOWN: {
//                     SDL_Point p = {eve.button.x, eve.button.y};
//                     if (SDL_PointInRect(&p, &gubbRect))
//                         drag = true;
//                     break;
//                 }
//                 case SDL_MOUSEBUTTONUP:
//                     drag = false;
//                     break;
//                 case SDL_MOUSEMOTION:
//                     if (drag) {
//                         gubbRect.x += eve.motion.xrel;
//                         gubbRect.y += eve.motion.yrel;
//                     }
//                     break;
//             }
//         }

//         // Rensar renderaren
//         SDL_RenderClear(ren);
//         // Kopierar bakgrundstexturen till renderaren
//         SDL_RenderCopy(ren, bgTx, NULL, NULL);
//         // Kopierar gubbbildens textur till renderaren
//         SDL_RenderCopy(ren, gubbTx, NULL, &gubbRect);
//         // Uppdaterar fönstret med det som har ritats
//         SDL_RenderPresent(ren);
//     }

//     // Frigör resurser och stänger SDL
//     SDL_DestroyTexture(gubbTx);
//     SDL_DestroyTexture(bgTx);
//     SDL_DestroyRenderer(ren);
//     SDL_DestroyWindow(win);
//     SDL_Quit();
//     return 0;
// }
