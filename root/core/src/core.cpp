#include "Nova/Desktop/core.h"
#include <Nova/Core/core.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_vulkan.h>
#include <vector>

namespace Nova::Desktop {
    bool Man::init(InitFlags f) {
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

    void Man::shutdown() {
        SDL_Quit();
    };

    bool Man::pollEvents(SDL_Event* event) {
        return SDL_PollEvent(event);
    }

    void Man::appendExtensions(std::vector<const char*>& extensions) {
        uint32_t extCount{};
        const char* const* sdlExtensions = SDL_Vulkan_GetInstanceExtensions(&extCount);
        if (!sdlExtensions || extCount == 0) {
            NERROR("SDL_Vulkan_GetInstanceExtensions failed: {} (returned no extensions)", SDL_GetError());
            return;
        }
        extensions.reserve(extensions.size() + extCount);
        extensions.insert(
            extensions.end(),
            sdlExtensions,
            sdlExtensions + extCount
        );

        return;
    };

    std::vector<const char*> Man::getExtensions() {
        std::vector<const char*> out{};
        this->appendExtensions(out);
        return out;
    };
};