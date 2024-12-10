#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern int tileMap[16][22];

void renderMap(SDL_Renderer* renderer, SDL_Texture* tileset, int tileMap[16][22], int tileWidth, int tileHeight, int scale);
void renderTile(SDL_Renderer* renderer, SDL_Texture* tileset, int tileIndex, int x, int y, int tileWidth, int tileHeight, int scale);
void renderNpcs(SDL_Renderer* renderer, SDL_Texture* sprites, int spriteWidth, int spriteHeight);


class render_window {
    public:
        render_window(const char* p_title, int p_w, int p_h);
        SDL_Texture* loadTexture(const char* p_filePath);
        void cleanUp();
        void clear();
        void render(SDL_Texture* p_tex, SDL_Rect* src, SDL_Rect* dest);
        SDL_Renderer* getRenderer();
        void display();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};
