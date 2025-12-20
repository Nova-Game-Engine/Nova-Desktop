#include "Nova/Desktop/window.hpp"
#include <vulkan/vulkan_core.h>

namespace Nova::Desktop {
    void Window::create(const std::string& title, const Core::Vec2& size, SDL_WindowFlags flags) {
        SDL_CreateWindow(title.c_str(), size.v[0], size.v[1], flags);
        
    };

    vk::SurfaceKHR& Window::createSurface(const vk::Instance& instance) {
        VkSurfaceKHR cSurface = VK_NULL_HANDLE;

        if (!SDL_Vulkan_CreateSurface(
                oHandle,
                static_cast<VkInstance>(instance),
                nullptr,
                &cSurface
            )) {
            throw std::runtime_error(SDL_GetError());
        }

        surface = vk::SurfaceKHR{cSurface};
        return surface;
    }

    vk::SurfaceKHR& Window::createSurface(const VkInstance& instance) {
        VkSurfaceKHR cSurface = VK_NULL_HANDLE;

        if (!SDL_Vulkan_CreateSurface(
                oHandle,
                instance,
                nullptr,
                &cSurface
            )) {
            throw std::runtime_error(SDL_GetError());
        }

        surface = vk::SurfaceKHR{cSurface};
        return surface;
    };

    void Window::destroy(const vk::Instance& instance) {
        if (surface != VK_NULL_HANDLE) {
            SDL_Vulkan_DestroySurface(static_cast<VkInstance>(instance), surface, nullptr);
        }
        SDL_DestroyWindow(oHandle);
    };

};