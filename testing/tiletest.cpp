#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>


void renderMap(SDL_Renderer* renderer, SDL_Texture* tileset, int tileMap[16][22], int tileWidth, int tileHeight, int scale);
void renderTile(SDL_Renderer* renderer, SDL_Texture* tileset, int tileIndex, int x, int y, int tileWidth, int tileHeight, int scale);

int tileMap[16][22] = {
    {11, 11, 12, 12, 11, 12, 12, 11, 11, 11, 12, 12, 11, 12, 11, 12, 11, 11, 11, 21, 11, 65},
    {12, 11, 12, 12, 11, 12, 12, 11, 11, 11, 12, 12, 11, 12, 11, 12, 11, 11, 12, 21, 11, 11},
    {11, 12, 12, 12, 11, 12, 12, 65, 65, 11, 65, 65, 65, 12, 11, 12, 11, 65, 65, 21, 11, 11},
    {11, 9, 9, 9, 9, 9, 9, 11, 11, 11, 12, 12, 65, 65, 11, 12, 11, 12, 11, 21, 11, 11},
    {11, 9, 17, 9, 9, 17, 9, 11, 11, 11, 12, 12, 11, 12, 11, 12, 11, 12, 11, 21, 11, 11},
    {11, 9, 9, 9, 9, 9, 9, 11, 11, 11, 65, 11, 11, 65, 11, 12, 11, 12, 11, 21, 11, 11},
    {65, 9, 9, 9, 9, 9, 9, 11, 65, 11, 12, 12, 11, 65, 65, 12, 11, 12, 11, 21, 11, 11},
    {65, 9, 17, 9, 9, 17, 9, 11, 11, 11, 12, 12, 11, 12, 11, 12, 11, 12, 11, 21, 11, 11},
    {65, 9, 9, 9, 9, 9, 9, 11, 11, 11, 65, 12, 11, 12, 11, 12, 11, 12, 11, 21, 11, 11},
    {11, 12, 12, 12, 11, 12, 12, 11, 11, 11, 12, 65, 11, 12, 11, 12, 11, 12, 11, 21, 11, 11},
    {11, 12, 12, 12, 11, 12, 65, 11, 11, 11, 11, 11, 11, 12, 65, 65, 65, 12, 11, 21, 11, 11},
    {11, 11, 12, 11, 11, 12, 12, 65, 65, 11, 12, 12, 11, 12, 11, 65, 65, 12, 11, 21, 11, 11},
    {11, 11, 12, 12, 11, 12, 12, 11, 11, 11, 12, 12, 11, 12, 11, 65, 65, 11, 11, 81, 65, 11},
    {11, 11, 12, 12, 11, 11, 12, 11, 11, 11, 11, 65, 65, 12, 11, 12, 11, 11, 65, 21, 65, 11},
    {11, 11, 12, 12, 11, 12, 12, 11, 11, 11, 12, 12, 65, 12, 11, 12, 11, 65, 11, 21, 11, 11},
    {11, 11, 12, 12, 11, 12, 11, 11, 11, 11, 12, 12, 11, 12, 11, 12, 11, 11, 12, 21, 11, 65}
};

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
        
        // This is to get the sprite tiles
        int spriteWidth = 16;
        int spriteHeight = 16;
        int row = spriteIndex / spritesPerRow;
        int col = spriteIndex % spritesPerRow;

        SDL_Rect Filberton = {col * spriteWidth, row * spriteHeight, spriteWidth, spriteHeight}; // still calling the boy Filberton
        SDL_RenderCopy(renderer, sprites, &Filberton, &playerRect);  

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

void renderMap(SDL_Renderer* renderer, SDL_Texture* tileset, int tileMap[16][22], int tileWidth, int tileHeight, int scale) {
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 22; x++) {
            int tileIndex = tileMap[y][x];
            renderTile(renderer, tileset, tileIndex, x * tileWidth * scale, y * tileHeight * scale, tileWidth, tileHeight, scale);
        }
    }
}

void renderTile(SDL_Renderer* renderer, SDL_Texture* tileset, int tileIndex, int x, int y, int tileWidth, int tileHeight, int scale) {
    int tilesPerRow = 8;

    int row = tileIndex / tilesPerRow; 
    int col = tileIndex % tilesPerRow;

    SDL_Rect srcRect = { col * tileWidth, row * tileHeight, tileWidth, tileHeight};
    SDL_Rect dstRect = { x, y, tileWidth * scale, tileHeight * scale};
    SDL_RenderCopy(renderer, tileset, &srcRect, &dstRect);
}


