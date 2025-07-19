// SDL2Project.cpp : Defines the entry point for the application.

// Using SDL and standard IO
#include <SDL.h>
#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH{640};
const int SCREEN_HEIGHT{480};

int main(int argc, char* args[])
{
    // The window we'll be rendering to
    SDL_Window* window = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
                  << std::endl;
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: "
                  << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: "
                  << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // The surface contained by the window
    SDL_Surface* screenSurface{SDL_GetWindowSurface(window)};

    // Fill the surface white
    SDL_FillRect(screenSurface, NULL,
                 SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(window);

    bool      running = true;
    SDL_Event event;
    float     t = 0.0f;

    // Main loop
    while (running)
    {
        // Handle events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Calculate color using sine waves (smooth cycling)
        Uint8 r = static_cast<Uint8>((std::sin(t) + 1.0f) * 127.5f);
        Uint8 g = static_cast<Uint8>((std::sin(t + 2.0f) + 1.0f) * 127.5f);
        Uint8 b = static_cast<Uint8>((std::sin(t + 4.0f) + 1.0f) * 127.5f);

        // Clear screen with calculated color
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        std::cout << (int)r << " " << (int)g << " " << (int)b << "\n";

        // Delay to control speed
        SDL_Delay(16); // ~60 FPS
        t += 0.02f;
    }

    SDL_DestroyWindow(window); // Destroy window
    SDL_Quit();                // Quit SDL subsystems

    return 0;
}
