#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "render_window.h"


render_window::render_window(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL) {
    
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, 
             SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cout << "Window failed to initialize: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

SDL_Texture* render_window::loadTexture(const char* p_filePath){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL){
        std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void render_window::clear(){
    SDL_RenderClear(renderer);
}

void render_window::render(SDL_Texture* p_tex, SDL_Rect* src, SDL_Rect* dest){
    SDL_RenderCopy(renderer, p_tex, src, dest);
}

void render_window::display(){
    SDL_RenderPresent(renderer);
}

void render_window::cleanUp(){
    SDL_DestroyWindow(window);
}

SDL_Renderer* render_window::getRenderer(){
    return renderer;
}

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

void renderNpcs(SDL_Renderer* renderer, SDL_Texture* sprites, int spriteWidth, int spriteHeight){
    int spritesPerRow = 12;
    
    SDL_Rect NPC1Rect = {400, 400, 72, 72};
    SDL_Rect NPC1 = {(10 % spritesPerRow) * spriteWidth, (10 / spritesPerRow) * spriteHeight, spriteWidth, spriteHeight};
    SDL_RenderCopy(renderer, sprites, &NPC1, &NPC1Rect);
    
    SDL_Rect NPC2Rect = {600, 400, 72, 72};
    SDL_Rect NPC2 = {(49 % spritesPerRow) * spriteWidth, (49 / spritesPerRow) * spriteHeight, spriteWidth, spriteHeight};
    SDL_RenderCopy(renderer, sprites, &NPC2, &NPC2Rect);
    
    SDL_Rect NPC3Rect = {512, 244, 72, 72};
    SDL_Rect NPC3 = {(55 % spritesPerRow) * spriteWidth, (55 / spritesPerRow) * spriteHeight, spriteWidth, spriteHeight};
    SDL_RenderCopy(renderer, sprites, &NPC3, &NPC3Rect);

}





