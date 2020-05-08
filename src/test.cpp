//
// Created by hugo on 5/7/20.
//
#include "Sprite.hpp"
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    SDL_Window* win = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* surf = nullptr;
    int width = 800, height = 600;

    SDL_Init(SDL_INIT_VIDEO);

    if (!(win = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 width, height, SDL_WINDOW_RESIZABLE))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        return 1;
    }

    if (!(renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
        return 2;
    }

    if (!(surf = SDL_GetWindowSurface(win))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize surface: %s",
                     SDL_GetError());
        return 3;
    }

    SpriteSheet test("../res/arrow.bmp", 3, 3);
    test.Draw(surf, 1, (int)(surf->w / 2 - test.SpriteWidth() / 2),
              (int)(surf->h / 2 - test.SpriteHeight() / 2));
    SDL_Texture* texture_test = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_test, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    bool running = true;
    while (running) {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            running = false;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}