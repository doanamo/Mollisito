#include "Shared.hpp"
#include "Math/Color.hpp"
#include "Render/Texture.hpp"

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
    SDL_Window* window = SDL_CreateWindow("Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 576,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(!window)
    {
        LOG_CRITICAL("Failed to create SDL window");
        return 1;
    }

    SCOPE_GUARD([window]()
    {
        SDL_DestroyWindow(window);
    });

    int windowWidth;
    int windowHeight;
    SDL_GetWindowSizeInPixels(window, &windowWidth, &windowHeight);
    LOG_INFO("Create window with {}x{} size", windowWidth, windowHeight);

    // Create frame texture
    Render::Texture frame(windowWidth, windowHeight,
        Render::Texture::ChannelType::Uint8, 3);

    // Create frame surface
    // It will be used to blit into window surface. We could avoid allocating
    // this, but then we would lose scaling functionality provided by SDL.
    SDL_Surface* frameSurface = SDL_CreateRGBSurface(
        0, frame.GetWidth(), frame.GetHeight(),
        32, 0, 0, 0, 0);

    // Start main loop
    bool quit = false;
    while(!quit)
    {
        // Process events
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // Render frame
        frame.Clear(Math::Color(0.0f, 0.5f, 0.5f));

        // Copy frame to surface
        auto frameSurfacePixels = (uint32_t*)frameSurface->pixels;
        for(int i = 0; i < frameSurface->w * frameSurface->h; ++i)
        {
            const uint8_t* framePixel = frame.GetPixelAddress(i);
            frameSurfacePixels[i] = SDL_MapRGBA(frameSurface->format,
                framePixel[0], framePixel[1], framePixel[2], 255);
        }

        // Copy surface to window and present
        SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
        SDL_BlitScaled(frameSurface, nullptr, windowSurface, nullptr);
        SDL_UpdateWindowSurface(window);
    }

    LOG_INFO("Exiting application...");
    return 0;
}
