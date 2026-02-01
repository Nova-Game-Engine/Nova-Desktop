#include <fmt/format.h>
#include <stdio.h>
#include <dlfcn.h>
#include <filesystem>
#include <chrono>
#include <thread>
#include <Nova/Desktop/core.h>

#include <Nova/Desktop/window.hpp>

int main() {
    Nova::Desktop::Man man;

    Nova::Desktop::CreateInfo::Man createInfo = Nova::Desktop::CreateInfo::Man::Builder()
        .enableVideo()
        .build();

    man.init(createInfo);

    Nova::Desktop::Window window;

    Nova::Desktop::CreateInfo::Window windowcreateInfo = Nova::Desktop::CreateInfo::Window::Builder()
        .setTitle("Nova Desktop test")
        .setSize({800, 600})
        .build();

    window.create(windowcreateInfo);
    //window.createSurface(nullptr);

    bool running = true;

    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }

    window.destroy(nullptr);

    man.shutdown();
}