#ifndef PROGRAM_IDRAWABLE_H
#define PROGRAM_IDRAWABLE_H

class SDL_Renderer;

class ISDLDrawable {
public:
    virtual void Draw(SDL_Renderer* Renderer) const = 0;
};

#endif //PROGRAM_IDRAWABLE_H
