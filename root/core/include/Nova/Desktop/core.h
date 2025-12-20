#pragma once
#include <Nova/Core/core.h>
#include <SDL3/SDL.h>
#include <string>
#include <vulkan/vulkan.hpp>
#include <cstdint>

namespace Nova::Desktop {
    using InitFlags = std::uint32_t;

    constexpr InitFlags INIT_VIDEO  = SDL_INIT_VIDEO;
    constexpr InitFlags INIT_AUDIO  = SDL_INIT_AUDIO;
    constexpr InitFlags INIT_GAMEPAD= SDL_INIT_GAMEPAD;
    constexpr InitFlags INIT_EVENTS = SDL_INIT_EVENTS;
    constexpr InitFlags INIT_JOYSTICK= SDL_INIT_JOYSTICK;
    constexpr InitFlags INIT_SENSOR = SDL_INIT_SENSOR;

    class Man {
        private:
            NOVA_LOG_DEF("Man");


        public:
            bool init(InitFlags flags);
            void shutdown();
            std::vector<const char*> getExtensions();
            void appendExtensions(std::vector<const char*>& extensions);

            bool pollEvents(SDL_Event* event); // Just a wrapper
    };
};