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
    man.Init(Nova::Desktop::INIT_VIDEO);

    Nova::Desktop::Window window;

    window.create("test", {100, 100});
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

    man.Shutdown();
}