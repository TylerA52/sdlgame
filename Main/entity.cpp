#include "entity.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex)
:x(p_x), y(p_y), tex(p_tex)
{
    currentFrame.x = 0; // This is the source - needs to change based on which part of the PNG I'm taking - how to do????
    currentFrame.y = 0;
    currentFrame.w = 16;
    currentFrame.h = 16;

}

float Entity::getX(){
    return x;
}

float Entity::getY(){
    return y;
}

SDL_Texture* Entity::getTex(){
    return tex;
}

SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}