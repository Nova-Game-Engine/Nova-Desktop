#include "Nova/Desktop/core.h"

namespace Nova::Desktop {
    bool Man::Init(InitFlags f) {
        if (f & INIT_VIDEO)   f |= INIT_EVENTS;
        if (f & INIT_GAMEPAD) f |= INIT_JOYSTICK | INIT_EVENTS;
        if (f & INIT_JOYSTICK)f |= INIT_EVENTS;
        if (f & INIT_SENSOR)  f |= INIT_EVENTS;

        bool out = SDL_Init(f);
        if (out) {
            NINFO("SDL initiated");
        }else {
            NERROR("SDL initiated unsuccessfully");
        }
        return out;
    };

    void Man::Shutdown() {
        SDL_Quit();
    };

    bool Man::PollEvents(SDL_Event* event) {
        return SDL_PollEvent(event);
    }
};