#ifndef SEABATTLE_RENDERER_H
#define SEABATTLE_RENDERER_H

#include <string>
#include <list>

#define WINDOW_HEIGHT 450
#define WINDOW_WIDTH 1200

class ISDLDrawable;
class SDL_Window;
class SDL_Renderer;

class CSDL_Renderer {
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;

public:
    std::list<const ISDLDrawable*> Drawables;

    CSDL_Renderer(int WindowWidth = WINDOW_WIDTH,
                  int WindowHeight = WINDOW_HEIGHT);
    ~CSDL_Renderer();

    void Render();

    inline SDL_Window* GetWindow() const;
    inline SDL_Renderer* GetRenderer() const;
private:
    void InitRenderer(const std::string& WindowCaption,
                      int WindowWidth,
                      int WindowHeight);

    void CloseRenderer();
};
#endif //SEABATTLE_RENDERER_H