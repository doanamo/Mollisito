#include "Common/Common.h"
#include <SDL.h>

int main(int argc, char* args[])
{
    // Initialize SDL library.
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return 1;
    }

    SCOPE_GUARD([]()
    {
        SDL_Quit();
    });

    // Create application window.
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 1024, 576, SDL_WINDOW_SHOWN);

    if(!window)
    {
        return 1;
    }

    SCOPE_GUARD([window]()
    {
        SDL_DestroyWindow(window);
    });

    // Start main loop.
    bool quit = false;
    while(!quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_UpdateWindowSurface(window);
    }

    return 0;
}
