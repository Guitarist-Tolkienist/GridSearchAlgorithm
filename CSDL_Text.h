#ifndef GRIDSEARCHALGORITHM_CSDL_TEXT_H
#define GRIDSEARCHALGORITHM_CSDL_TEXT_H

#include <string>
#include "SDL2/SDL.h"
#include "ISDLDrawable.h"

typedef struct _TTF_Font TTF_Font;

class CSDLText : public ISDLDrawable {
    std::string TextString;
    TTF_Font* Font = nullptr;
    SDL_Surface* TextSurface = nullptr;

    SDL_Color ForegroundColor;
    SDL_Rect TextLocation;
public:
    explicit CSDLText(const char* CharString, int FontSize = 35, const char* FontName = "Konstanting.ttf", int PosX = 0, int PosY = 0);
    ~CSDLText();

    void SetTextPosition(int X, int Y);

    void SetText(const char* NewText);

    void Draw(SDL_Renderer* Renderer) const override;
};

#endif //GRIDSEARCHALGORITHM_CSDL_TEXT_H
