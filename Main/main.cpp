#include "render_window.h"
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
    
    render_window window("GAME", windowWidth, windowHeight);
    SDL_Renderer* renderer = window.getRenderer();
    // Map Tileset
    SDL_Texture* tileset = window.loadTexture("/home/tyler/Desktop/sdlgame/tileset/basictiles.png");
    if (!tileset) {
        std::cerr << "Error loading tileset image: " << IMG_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    // Character sprites
    SDL_Texture* sprites = window.loadTexture("/home/tyler/Desktop/sdlgame/Images/characters.png");
    if (!sprites) {
        std::cerr << "Error loading tileset image: " << IMG_GetError() << '\n';
        SDL_Quit();
        return 1;
    }
    

    int tileWidth = 16;
    int tileHeight = 16;
    int tilesPerRow = 8;

    int spritesPerRow = 12;
    int spriteIndex = 3;

    SDL_Rect playerRect = {164, 224, 72, 72};

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

        window.clear();
                                
        int scale = 3; // Using this to make tiles appear bigger
        
        int spriteWidth = 16;
        int spriteHeight = 16;

        renderMap(renderer, tileset, tileMap, tileWidth, tileHeight, scale);
        renderNpcs(renderer, sprites, spriteWidth, spriteHeight);

        // This is to get the sprite tiles for the player - spriteIndex is for player sprites
        int row = spriteIndex / spritesPerRow;
        int col = spriteIndex % spritesPerRow;
        
        SDL_Rect Filberton = {col * spriteWidth, row * spriteHeight, spriteWidth, spriteHeight}; // still calling the boy Filberton
        window.render(sprites, &Filberton, &playerRect);  
        
        window.display();
    }
    
    // Cleanup

    SDL_DestroyTexture(tileset);
    SDL_DestroyTexture(sprites);
    window.cleanUp();
    SDL_Quit();

    return 0;
}


