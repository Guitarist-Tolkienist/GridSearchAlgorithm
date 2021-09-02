#include "CSDL_Controller.h"
#include "CWorld.h"

CSDL_Controller::CSDL_Controller() {

}

bool CSDL_Controller::UpdateEvent() {
    bool CanAppRun = true;

    while (SDL_PollEvent(&Event)) {
        // KEYBOARD EVENTS
        switch (Event.type) {
            case SDL_QUIT:
                break;
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        break;
                    case SDLK_LEFT:
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_UP:
                        break;
                    case SDLK_ESCAPE:
                        CanAppRun = false;
                        break;
                    case SDLK_SPACE:
                        WorldData->bDoNextstep = true;
                        break;
                    default :
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN: {
            }break;
            default:
                break;
        }
    }

    return CanAppRun;
}
