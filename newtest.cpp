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
    
    //chat jippity reccommended these checks to see if things work or no

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

    SDL_Texture* filberton = IMG_LoadTexture(renderer, "/home/tyler/Desktop/sdlgame/Images/Untitled.png");

    if (!filberton) {
        std::cerr << "Error loading image: " << IMG_GetError() << '\n';
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect imageRect = { windowWidth / 2 - 50, windowHeight / 2 - 50, 250, 250 };

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
                        imageRect.y -= 20;
                    }
                    if (event.key.keysym.sym == SDLK_a) {
                        imageRect.x -= 20;
                    }
                    if (event.key.keysym.sym == SDLK_s) {
                        imageRect.y += 20;  
                    }
                    if (event.key.keysym.sym == SDLK_d) {
                        imageRect.x += 20;
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, filberton, nullptr, &imageRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(filberton);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

