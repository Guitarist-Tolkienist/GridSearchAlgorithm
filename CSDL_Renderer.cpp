#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "CSDL_Renderer.h"
#include "CSDL_Text.h"

CSDL_Renderer::CSDL_Renderer(int WindowWidth, int WindowHeight) {
    std::string Caption("Window");

    SDL_Init(SDL_INIT_VIDEO);

    InitRenderer(Caption, WindowWidth, WindowHeight);

    TTF_Init();
}

CSDL_Renderer::~CSDL_Renderer() {
    SDL_Quit();

    CloseRenderer();

    TTF_Quit();
}

SDL_Window* CSDL_Renderer::GetWindow() const {
    return Window;
}

SDL_Renderer* CSDL_Renderer::GetRenderer() const {
    return Renderer;
}

void CSDL_Renderer::InitRenderer(const std::string& WindowCaption,
                                 int WindowWidth,
                                 int WindowHeight) {
    Window = SDL_CreateWindow(WindowCaption.c_str(),
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                              WindowWidth,
                              WindowHeight,
                         SDL_WINDOW_RESIZABLE);
    if (Window == NULL) {
        fprintf(stderr, "SDL CreateWindow failed: %s", SDL_GetError());
    }

    Renderer = SDL_CreateRenderer(Window,
                            -1,
                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == NULL) {
        fprintf(stderr, "SDL CreateRenderer failed %s", SDL_GetError());
        exit(1);
    }
}

void CSDL_Renderer::CloseRenderer() {
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
}

void CSDL_Renderer::Render() {
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);

    for (auto Drawable: Drawables) {
        Drawable->Draw(Renderer);
    }

    SDL_RenderPresent(Renderer);
}
