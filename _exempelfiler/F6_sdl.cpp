#include <SDL2/SDL.h> // Inkluderar SDL2-biblioteket för att använda SDL-funktioner
#include <iostream>   // Inkluderar iostream för att använda std::cerr och std::endl
#include <string>     // Inkluderar string för att använda std::string
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;  // Använder standardnamnrymden för att slippa skriva std:: före varje standardfunktion
#define FPS 60

// Definierar sökvägarna till bilderna
string bgPath = "C:/Users/amire/Downloads/cprog_template_win_241106/resources/images/bg2.bmp";
string gubbPath = "D:/random files/random images/download_jpeg.bmp";

int main(int argc, char* argv[]) {
    // Initierar SDL2-biblioteket för videofunktioner
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        cerr << "SDL_Init error: " << SDL_GetError() << endl; exit(-1);
    }
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("c:/Windows/Fonts/arial.ttf", 36);
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);

   Mix_Chunk* musik = Mix_LoadWAV("D:/resources/sound/thick-of-it.wav"); 
    // Skapar ett fönster med titeln "Mitt" och storleken 600x500 pixlar
    Mix_Chunk* skott = Mix_LoadWAV("D:/resources/sound/thick-of-it-brainrot.wav"); 
    
    SDL_Window* win = SDL_CreateWindow("Mitt",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 500, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        cerr << "Window creation error: " << SDL_GetError() << endl; SDL_Quit(); exit(-1);
    }

    // Skapar en renderer som används för att rita i fönstret
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        cerr << "Renderer creation error: " << SDL_GetError() << endl; SDL_DestroyWindow(win); SDL_Quit(); exit(-1);
    }

    // Laddar bakgrundsbilden från filen
    SDL_Surface* bgSurf = SDL_LoadBMP(bgPath.c_str());
    // Skapar en textur från bakgrundsbilden
    SDL_Texture* bgTx = SDL_CreateTextureFromSurface(ren, bgSurf); SDL_FreeSurface(bgSurf);

    // Laddar gubbbilden från filen
    SDL_Surface* gubbSurf = SDL_LoadBMP(gubbPath.c_str());
    // Skapar en rektangel som representerar gubbbildens position och storlek
    SDL_Rect gubbRect = {0, 0, gubbSurf->w, gubbSurf->h};
    // Definierar vit färg för att använda som genomskinlig färg
    Uint32 white = SDL_MapRGB(gubbSurf->format, 255, 255, 255);
    // Sätter vit färg som genomskinlig i gubbbilden
    SDL_SetColorKey(gubbSurf, SDL_TRUE, white);
    // Skapar en textur från gubbbilden
    SDL_Texture* gubbTx = SDL_CreateTextureFromSurface(ren, gubbSurf); SDL_FreeSurface(gubbSurf);

    SDL_Surface* donkSurf = IMG_Load("D:/Plugg/WEB1/tests/images/th.jpeg");
    SDL_Texture* donkTx = SDL_CreateTextureFromSurface(ren, donkSurf);
    SDL_Rect donkRect = {200, 200, donkSurf->w, donkSurf->h};
    SDL_FreeSurface(donkSurf);

    // Variabel för att hålla reda på om programmet ska fortsätta köra
    bool runOn = true, drag = false;
    int varv = 0;
    
    const int thickInterval = 1000 / FPS;
    
    int channel = Mix_PlayChannel(-1, musik, -1);
    Mix_Volume(1, 5);

    while (runOn) {
        SDL_Event eve;
        // Hanterar händelser (t.ex. tangenttryckningar, musrörelser)
        while (SDL_PollEvent(&eve)) {
            switch (eve.type) {
                case SDL_QUIT:
                    runOn = false;
                    break;
                case SDL_KEYDOWN:
                    switch(eve.key.keysym.sym) {
                        case SDLK_UP:
                            gubbRect.y-=10;
                            Mix_Volume(channel, gubbRect.y);
                            break;
                        case SDLK_DOWN:
                            gubbRect.y+=10;
                            Mix_Volume(channel, gubbRect.y);
                            break;
                        case SDLK_LEFT:
                            gubbRect.x-=10;
                            break;
                        case SDLK_RIGHT:
                            gubbRect.x+=10;
                            break;
                    }
                    
                    if (eve.key.keysym.sym == SDLK_END)
                        runOn = false;
                    break;
                case SDL_MOUSEBUTTONDOWN: {
                    SDL_Point p = {eve.button.x, eve.button.y};
                    if (SDL_PointInRect(&p, &gubbRect))
                        drag = true;
                    Mix_PlayChannel(-1, skott, 1);
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                    drag = false;
                    break;
                case SDL_MOUSEMOTION:
                    if (drag) {
                        gubbRect.x += eve.motion.xrel;
                        gubbRect.y += eve.motion.yrel;
                    }
                    break;
            }
        }
        
        varv++;
        string varvStr = to_string(varv);
        SDL_Color svart = {0,0,0};
        SDL_Surface* varvSurf = TTF_RenderText_Solid(font, varvStr.c_str(), svart); 
        SDL_Texture* varvTxt = SDL_CreateTextureFromSurface(ren, varvSurf);
        SDL_Rect varvRect = {300, 300,varvSurf->w,varvSurf->h};
        SDL_FreeSurface(varvSurf);
         

        // Rensar renderaren
        SDL_RenderClear(ren);
        // Kopierar bakgrundstexturen till renderaren
        SDL_RenderCopy(ren, bgTx, NULL, NULL);
        // Kopierar gubbbildens textur till renderaren
        SDL_RenderCopy(ren, gubbTx, NULL, &gubbRect);
        SDL_RenderCopy(ren, varvTxt, NULL, &varvRect);
        // Uppdaterar fönstret med det som har ritats
        SDL_RenderPresent(ren);
        SDL_DestroyTexture(varvTxt);
    }

    // Frigör resurser och stänger SDL
    Mix_FreeChunk(musik);
    TTF_CloseFont(font);
    SDL_DestroyTexture(gubbTx);
    SDL_DestroyTexture(bgTx);
    SDL_DestroyTexture(donkTx);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
}