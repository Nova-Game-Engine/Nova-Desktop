#pragma once

#include <Nova/Core/structs.hpp>
#include <SDL3/SDL.h>
#include <Nova/Core/core.h>
#include <vulkan/vulkan.hpp>
#include <SDL3/SDL_vulkan.h>

namespace Nova::Desktop {
    class Window {
        private:
            SDL_Window *oHandle;
            NOVA_LOG_DEF("Window");
            vk::SurfaceKHR surface = VK_NULL_HANDLE;

        public:
            Window() {
                if(!SDL_WasInit(SDL_INIT_VIDEO)) {
                    NINFO("SDL_INIT_VIDEO not initiated");
                }
            };
            ~Window() {};

        public:
            void create(const std::string& title, const Core::Vec2& size, SDL_WindowFlags flags = SDL_WINDOW_VULKAN | SDL_WINDOWPOS_CENTERED);
            void destroy(const vk::Instance& instance);
            vk::SurfaceKHR& createSurface(const vk::Instance& instance);
        
        public:
            SDL_Window& get() {return *oHandle;}
    };
};