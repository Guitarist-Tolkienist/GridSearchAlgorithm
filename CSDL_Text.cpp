#include "CSDL_Text.h"
#include "SDL2/SDL_ttf.h"

CSDLText::CSDLText(const char* CharString, int FontSize, const char* FontName, int PosX, int PosY) : TextLocation{PosX, PosY, 0, 0} {
    TextString = CharString;

    Font = TTF_OpenFont(FontName, FontSize);

    ForegroundColor = { 255, 255, 255, 255 };

    TextSurface = TTF_RenderText_Solid(Font, TextString.c_str(), ForegroundColor);
}

CSDLText::~CSDLText() {
    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);
}

void CSDLText::Draw(SDL_Renderer* Renderer) const {
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, TextSurface);

    SDL_Rect Location = TextLocation;
    SDL_QueryTexture(Texture, NULL, NULL, &Location.w, &Location.h);

    SDL_RenderCopy(Renderer, Texture, NULL, &Location);
}

void CSDLText::SetTextPosition(int X, int Y) {
    TextLocation.x = X < 0 ? TextLocation.x : X;
    TextLocation.y = Y < 0 ? TextLocation.y : Y;
}

void CSDLText::SetText(const char* NewText) {
    TextString = NewText;
    TextSurface = TTF_RenderText_Solid(Font, TextString.c_str(), ForegroundColor);
}
