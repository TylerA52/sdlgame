#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "render_window.h"
#include "entity.h"


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

void render_window::render(Entity& p_entity){
    
    SDL_Rect src;
    src.x = p_entity.getCurrentFrame().x; // This is the source - how do I get this????
    src.y = p_entity.getCurrentFrame().y;
    src.w = p_entity.getCurrentFrame().w;
    src.h = p_entity.getCurrentFrame().h;

    // Add transformations on all values
    SDL_Rect dst;
    dst.x = p_entity.getX();
    dst.y = p_entity.getY();
    dst.w = p_entity.getCurrentFrame().w * 4.5;
    dst.h = p_entity.getCurrentFrame().h * 4.5;


    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
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







