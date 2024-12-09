#include "game.h"
#include <iostream>


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




