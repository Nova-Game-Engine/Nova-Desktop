#pragma once

#include "Nova/Desktop/core.h"
#include <Nova/Core/structs.hpp>
#include <SDL3/SDL.h>
#include <Nova/Core/core.h>
#include <vulkan/vulkan.hpp>
#include <SDL3/SDL_vulkan.h>

namespace Nova::Desktop {

    namespace CreateInfo {
        struct Window {
            std::string title = "Nova Engine Window";
            Core::Vec2 size = {800, 600};
            SDL_WindowFlags flags = SDL_WINDOW_VULKAN;

            class Builder {
                private:Window* info;
                public: Builder() : info(new Window()) {};
                ~Builder() {if (info != nullptr) delete info;};
                Builder& setTitle(const std::string& title) {info->title = title; return *this;};
                Builder& setSize(const Core::Vec2& size) {info->size = size; return *this;};
                Builder& setFlags(SDL_WindowFlags flags) {info->flags = flags; return *this;};
                Builder& setCenteredPosition() {info->flags |= SDL_WINDOWPOS_CENTERED; return *this;};
                Builder& setFullscreen() {info->flags |= SDL_WINDOW_FULLSCREEN; return *this;};
                Builder& setBorderless() {info->flags |= SDL_WINDOW_BORDERLESS; return *this;};
                Builder& setResizable() {info->flags |= SDL_WINDOW_RESIZABLE; return *this;};
                Builder& setMaximized() {info->flags |= SDL_WINDOW_MAXIMIZED; return *this;};
                Window& build() {return *info;};      
            };
        };
    };

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
            void create(Nova::Desktop::CreateInfo::Window& CreateInfo);
            void destroy(const vk::Instance& instance);

            INTERNAL vk::SurfaceKHR& createSurface(const vk::Instance& instance);
            INTERNAL vk::SurfaceKHR& createSurface(const VkInstance& instance);
        
        public:
            SDL_Window& get() {return *oHandle;}
    };
};