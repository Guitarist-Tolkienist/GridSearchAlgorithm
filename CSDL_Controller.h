#ifndef PROGRAM_CSDL_CONTROLLER_H
#define PROGRAM_CSDL_CONTROLLER_H

#include <SDL2/SDL.h>

class CWorld;

class CSDL_Controller {
    SDL_Event Event;

public:
    CWorld* WorldData;
    CSDL_Controller();

    bool UpdateEvent();
};


#endif //PROGRAM_CSDL_CONTROLLER_H
