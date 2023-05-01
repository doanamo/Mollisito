#include "Shared.hpp"
#include "Application.hpp"

int main(int argc, char* args[])
{
    Common::SetupLogger();

    // Global settings
    bool requestHardwarePresent = true;
    bool requestPresentVsync = false;
    float resolutionScale = 1.0f;

    // Initialize SDL
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

    // Create window
    const char* windowTitle = "Game";
    SDL_Window* window = SDL_CreateWindow(windowTitle,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 576,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(!window)
    {
        LOG_CRITICAL("Failed to create SDL window");
        return 1;
    }

    SCOPE_GUARD([&window]()
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    });

    int windowWidth;
    int windowHeight;
    SDL_GetWindowSizeInPixels(window, &windowWidth, &windowHeight);
    LOG_INFO("Created window with {}x{} size", windowWidth, windowHeight);

    // Create renderer
    uint32_t rendererFlags = 0;
    if(requestHardwarePresent)
    {
        rendererFlags |= SDL_RENDERER_ACCELERATED;
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    }
    else
    {
        rendererFlags |= SDL_RENDERER_SOFTWARE;
    }

    if(requestPresentVsync)
    {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if(!renderer)
    {
        LOG_CRITICAL("Failed to create SDL renderer");
        return 1;
    }

    SCOPE_GUARD([&renderer]()
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    });

    SDL_RenderSetVSync(renderer, requestPresentVsync ? SDL_TRUE : SDL_FALSE);

    SDL_RendererInfo rendererInfo;
    if(SDL_GetRendererInfo(renderer, &rendererInfo) != 0)
    {
        LOG_CRITICAL("Failed to retrieve SDL renderer info");
        return 1;
    }

    LOG_INFO("Created SDL renderer: {}", rendererInfo.name);
    LOG_INFO("Renderer hardware acceleration: {}",
        (rendererInfo.flags & SDL_RENDERER_ACCELERATED) != 0);
    LOG_INFO("Renderer present vsync: {}",
        (rendererInfo.flags & SDL_RENDERER_PRESENTVSYNC) != 0);
    LOG_INFO("Renderer available texture formats:");
    for(uint32_t i = 0; i < rendererInfo.num_texture_formats; ++i)
    {
        LOG_INFO("  {}", SDL_GetPixelFormatName(
            rendererInfo.texture_formats[i]));
    }

    // Create texture
    SDL_Texture* texture = nullptr;
    Graphics::Image::BufferInfo imageBufferInfo;
    auto createTexture = [&]()
    {
        if(texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
            windowWidth * resolutionScale, windowHeight * resolutionScale);

        if(!texture)
        {
            LOG_CRITICAL("Failed to create SDL texture");
            return false;
        }

        SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);

        imageBufferInfo = {};
        SDL_QueryTexture(texture, nullptr, nullptr,
            &imageBufferInfo.width,
            &imageBufferInfo.height);

        if(rendererInfo.flags & SDL_RENDERER_SOFTWARE)
        {
            // Use texture data directly if software renderer is used
            SDL_LockTexture(texture, nullptr,
                &imageBufferInfo.pixels,
                &imageBufferInfo.pitch);
        }

        return true;
    };

    if(!createTexture())
    {
        return 1;
    }

    SCOPE_GUARD([&texture]()
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    });

    // Create application
    Application::SetupInfo applicationSetup{};
    applicationSetup.renderer.frameBuffer = imageBufferInfo;

    Application application;
    if(!application.Setup(applicationSetup))
    {
        LOG_CRITICAL("Failed to setup application");
        return 1;
    }

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

        // Display frame rate
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

                    if(!createTexture())
                    {
                        LOG_CRITICAL("Failed to recreate SDL texture");
                        return 1;
                    }

                    Application::ResizeInfo resizeInfo;
                    resizeInfo.frameBuffer = imageBufferInfo;

                    if(!application.OnResize(resizeInfo))
                    {
                        LOG_CRITICAL("Failed to resize application");
                        return 1;
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

        // Upload texture data
        if(rendererInfo.flags & SDL_RENDERER_ACCELERATED)
        {
            const Graphics::Image& frame = application.GetRenderer().GetFrameColor().GetImage();
            SDL_UpdateTexture(texture, nullptr, frame.GetPixels(), frame.GetPitch());
        }

        // Present frame
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    LOG_INFO("Exiting application...");
    return 0;
}
