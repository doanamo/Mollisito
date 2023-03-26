#include "Shared.hpp"
#include "Application.hpp"

int main(int argc, char* args[])
{
    Common::SetupLogger();

    // Global flags
    bool enableHardwarePresent = true;
    bool enableHardwarePresentVsync = false;

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
    const char* windowTitle = "Game";
    SDL_Window* window = SDL_CreateWindow(windowTitle,
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

    // Create hardware renderer for presenting
    SDL_Renderer* renderer = nullptr;
    if(enableHardwarePresent)
    {
        uint32_t flags = SDL_RENDERER_ACCELERATED;
        if(enableHardwarePresentVsync)
        {
            flags |= SDL_RENDERER_PRESENTVSYNC;
        }

        renderer = SDL_CreateRenderer(window, -1, flags);

        if(!renderer)
        {
            LOG_WARNING("Failed to create SDL renderer");
            LOG_WARNING("Falling back to software present");
            enableHardwarePresent = false;
        }
    }

    SCOPE_GUARD([renderer]()
    {
        SDL_DestroyRenderer(renderer);
    });

    // Create application instance
    Application::SetupInfo applicationSetup{};
    applicationSetup.windowWidth = windowWidth;
    applicationSetup.windowHeight = windowHeight;

    Application application;
    if(!application.Setup(applicationSetup))
    {
        LOG_CRITICAL("Failed to setup application instance");
        return 1;
    }

    const Graphics::Texture& frame = application.GetRenderer().GetFrame();

    // Create frame texture
    SDL_Texture* frameTexture = nullptr;
    auto createFrameTexture = [&]()
    {
        if(frameTexture)
        {
            SDL_DestroyTexture(frameTexture);
            frameTexture = nullptr;
        }

        if(enableHardwarePresent)
        {
            frameTexture = SDL_CreateTexture(renderer,
                SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                frame.GetWidth(), frame.GetHeight());

            if(!frameTexture)
            {
                LOG_WARNING("Failed to create SDL texture");
                LOG_WARNING("Falling back to software present");
                enableHardwarePresent = false;
            }

            SDL_SetTextureScaleMode(frameTexture, SDL_ScaleModeNearest);
        }

        return true;
    };

    if(!createFrameTexture())
        return 1;

    SCOPE_GUARD([frameTexture]()
    {
        SDL_DestroyTexture(frameTexture);
    });

    // Create frame surface
    // It will be used to blit into window surface. We could avoid allocating
    // this, but then we would lose scaling functionality provided by SDL.
    SDL_Surface* frameSurface = nullptr;
    auto createFrameSurface = [&]()
    {
        if(frameSurface)
        {
            SDL_FreeSurface(frameSurface);
            frameSurface = nullptr;
        }

        if(!enableHardwarePresent)
        {
            frameSurface = SDL_CreateRGBSurface(
                0, frame.GetWidth(), frame.GetHeight(), 32,
                0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

            if(!frameSurface)
            {
                LOG_CRITICAL("Failed to create SDL surface");
                return false;
            }
        }

        return true;
    };

    if(!createFrameSurface())
        return 1;

    SCOPE_GUARD([frameSurface]()
    {
        SDL_FreeSurface(frameSurface);
    });

    // Start main loop
    uint64_t timeCurrent = SDL_GetPerformanceCounter();
    uint64_t timePrevious = timeCurrent;
    float frameRateUpdateDelay = 0.1f;

    while(true)
    {
        // Calculate delta time
        timePrevious = timeCurrent;
        timeCurrent = SDL_GetPerformanceCounter();

        float deltaTime = (float)((double)(timeCurrent - timePrevious)
            / (double)SDL_GetPerformanceFrequency());

        // Display framerate
        frameRateUpdateDelay -= deltaTime;
        if(frameRateUpdateDelay < 0.0f)
        {
            std::string windowTitleNew = fmt::format("{} ({:.2f} FPS)",
                windowTitle, 1.0f / deltaTime);

            SDL_SetWindowTitle(window, windowTitleNew.c_str());
            frameRateUpdateDelay = 1.0f;
        }

        // Process events
        bool quit = false;

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                LOG_INFO("Application exit requested by user");
                quit = true;
            }
            else if(event.type == SDL_WINDOWEVENT)
            {
                if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    windowWidth = event.window.data1;
                    windowHeight = event.window.data2;
                    LOG_INFO("Window size changed to {}x{}", windowWidth, windowHeight);

                    if(!application.OnResize(windowWidth, windowHeight) ||
                        !createFrameTexture() || !createFrameSurface())
                    {
                        LOG_CRITICAL("Failed to resize window");
                        quit = true;
                    }
                }
            }
        }

        if(quit)
        {
            break;
        }

        // Frame processing
        application.OnFrame(deltaTime);

        // Present frame
        if(enableHardwarePresent)
        {
            SDL_UpdateTexture(frameTexture, nullptr, frame.GetData(), frame.GetPitch());
            SDL_RenderCopy(renderer, frameTexture, nullptr, nullptr);
            SDL_RenderPresent(renderer);
        }
        else
        {
            // Copy frame to surface
            auto frameSurfacePixels = (uint32_t*)frameSurface->pixels;
            memcpy(frameSurfacePixels, frame.GetData(), frame.GetDataSize());

            // Copy surface to window and present
            SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
            SDL_BlitScaled(frameSurface, nullptr, windowSurface, nullptr);
            SDL_UpdateWindowSurface(window);
        }
    }

    LOG_INFO("Exiting application...");
    return 0;
}
