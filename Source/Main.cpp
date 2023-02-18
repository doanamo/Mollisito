#include "Common/Common.hpp"
#include <SDL.h>

int main(int argc, char* args[])
{
    Common::SetupLogger();

    // Initialize SDL library
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_CRITICAL("Failed to initialize SDL library");
        return 1;
    }

    SCOPE_GUARD([]()
    {
        SDL_Quit();
    });

    SDL_version sdlVersion{};
    SDL_GetVersion(&sdlVersion);
    LOG_INFO("Initialized SDL {}.{}.{} library",
        sdlVersion.major, sdlVersion.minor, sdlVersion.patch);

    // Create application window
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 1024, 576, SDL_WINDOW_SHOWN);

    if(!window)
    {
        LOG_CRITICAL("Failed to create SDL window");
        return 1;
    }

    SCOPE_GUARD([window]()
    {
        SDL_DestroyWindow(window);
    });

    int windowWidth, windowHeight;
    SDL_GetWindowSizeInPixels(window, &windowWidth, &windowHeight);
    LOG_INFO("Create window with {}x{} size", windowWidth, windowHeight);

    // Start main loop
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

    LOG_INFO("Exiting application...");
    return 0;
}
