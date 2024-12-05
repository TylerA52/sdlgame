#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>

int main(int argc, char* argv[]){

    int windowWidth = 800;
    int windowHeight = 600;


    if (argc == 3){
        windowWidth = std::atoi(argv[1]);
        windowHeight = std::atoi(argv[2]);
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization failed: " << SDL_GetError();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                       windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError();
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Event event;

    bool isRunning = true;
    bool keyPressed = false;

    while (isRunning) {
        while(SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_w){
                        std::cout << "W" << '\n';
                    }
                    if (event.key.keysym.sym == SDLK_a){
                        std::cout << "A " << '\n';
                    }
                    if (event.key.keysym.sym == SDLK_s){
                        std::cout << "S " << '\n';
                    }
                    if (event.key.keysym.sym == SDLK_d){
                        std::cout << "D " << '\n';
                    }
                    break;
            }

        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}





