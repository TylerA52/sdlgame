#include "game.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>


int main(int argc, char* argv[]) {
    int windowWidth = 1024;
    int windowHeight = 768;

    if (argc == 3) {
        windowWidth = std::atoi(argv[1]);
        windowHeight = std::atoi(argv[2]);
    }
    

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization failed: " << SDL_GetError() << '\n';
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "SDL Image initialization failed: " << IMG_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Map Tileset

    SDL_Texture* tileset = IMG_LoadTexture(renderer, "/home/tyler/Desktop/sdlgame/tileset/basictiles.png");
    if (!tileset) {
        std::cerr << "Error loading tileset image: " << IMG_GetError() << '\n';
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Character sprites

    SDL_Texture* sprites = IMG_LoadTexture(renderer, "/home/tyler/Desktop/sdlgame/Images/characters.png");
    if (!tileset) {
        std::cerr << "Error loading tileset image: " << IMG_GetError() << '\n';
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int tileWidth = 16;
    int tileHeight = 16;
    int tilesPerRow = 8;

    int spritesPerRow = 12;
    int spriteIndex = 3;

    SDL_Rect playerRect = {164, 224, 72, 72};
    SDL_Rect NPC1Rect =  {400, 400, 72, 72};


    bool isRunning = true;

    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_w) {
                        playerRect.y -= 24;
                        spriteIndex = 39;
                    }
                    if (event.key.keysym.sym == SDLK_a) {
                        playerRect.x -= 24;
                        spriteIndex = 15;
                    }
                    if (event.key.keysym.sym == SDLK_s) {
                        playerRect.y += 24;
                        spriteIndex = 3;
                    }
                    if (event.key.keysym.sym == SDLK_d) {
                        playerRect.x += 27;
                        spriteIndex = 27;
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);
                                
        int scale = 3; // Using this to make tiles appear bigger

        renderMap(renderer, tileset, tileMap, tileWidth, tileHeight, scale);
        
        // This is to get the sprite tiles for the player - spriteIndex is for player sprites
        int spriteWidth = 16;
        int spriteHeight = 16;
        int row = spriteIndex / spritesPerRow;
        int col = spriteIndex % spritesPerRow;
        
        int npcIndex = 10;
        int npcRow = npcIndex / spritesPerRow;
        int npcCol = npcIndex % spritesPerRow;

        SDL_Rect Filberton = {col * spriteWidth, row * spriteHeight, spriteWidth, spriteHeight}; // still calling the boy Filberton
        SDL_RenderCopy(renderer, sprites, &Filberton, &playerRect);  
        
        SDL_Rect NPC1 = {npcCol * spriteWidth, npcRow * spriteHeight, spriteWidth, spriteHeight};
        SDL_RenderCopy(renderer, sprites, &NPC1, &NPC1Rect);  

        SDL_RenderPresent(renderer);
    }
    
    // Cleanup

    SDL_DestroyTexture(tileset);
    SDL_DestroyTexture(sprites);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


