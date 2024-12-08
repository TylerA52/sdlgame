
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern int tileMap[16][22];

void renderMap(SDL_Renderer* renderer, SDL_Texture* tileset, int tileMap[16][22], int tileWidth, int tileHeight, int scale);
void renderTile(SDL_Renderer* renderer, SDL_Texture* tileset, int tileIndex, int x, int y, int tileWidth, int tileHeight, int scale);

#endif
