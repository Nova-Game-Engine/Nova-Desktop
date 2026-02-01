#pragma once
#include <Nova/Core/core.h>
#include <SDL3/SDL.h>
#include <string>
#include <vulkan/vulkan.hpp>
#include <cstdint>

#if defined(__clang__) || defined(__GNUC__)
    #define INTERNAL [[deprecated("Internal use only")]]
#elif defined(_MSC_VER)
    #define INTERNAL __declspec(deprecated("Internal use only"))
#else
    #define INTERNAL
#endif


namespace Nova::Desktop {

    using InitFlags = std::uint32_t;

    constexpr InitFlags INIT_VIDEO  = SDL_INIT_VIDEO;
    constexpr InitFlags INIT_AUDIO  = SDL_INIT_AUDIO;
    constexpr InitFlags INIT_GAMEPAD= SDL_INIT_GAMEPAD;
    constexpr InitFlags INIT_EVENTS = SDL_INIT_EVENTS;
    constexpr InitFlags INIT_JOYSTICK= SDL_INIT_JOYSTICK;
    constexpr InitFlags INIT_SENSOR = SDL_INIT_SENSOR;

    namespace CreateInfo {
        struct Man {
            InitFlags flags = INIT_VIDEO | INIT_EVENTS;


            class Builder {
                private:Man* info;
                public:
                    Builder() : info(new Man()) {};
                    ~Builder() {if (info != nullptr) delete info;};
                    Builder& enableVideo() {info->flags |= INIT_VIDEO; return *this;};
                    Builder& enableAudio() {info->flags |= INIT_AUDIO; return *this;};
                    Builder& enableGamepad() {info->flags |= INIT_GAMEPAD; return *this;};
                    Builder& enableEvents() {info->flags |= INIT_EVENTS; return *this;};
                    Builder& enableJoystick() {info->flags |= INIT_JOYSTICK; return *this;};
                    Builder& enableSensor() {info->flags |= INIT_SENSOR; return *this;};
                    Man& build() {return *info;};
            };
        };
    };

    class Man {
        private:
            NOVA_LOG_DEF("Man");


        public:

            Man(CreateInfo::Man& CreateInfo) {}
            Man() {};
            ~Man() {shutdown();}

            bool init(CreateInfo::Man& CreateInfo);
            void shutdown();


            std::vector<const char*> getExtensions();
            void appendExtensions(std::vector<const char*>& extensions);

            bool pollEvents(SDL_Event* event); // Just a wrapper
    };
};