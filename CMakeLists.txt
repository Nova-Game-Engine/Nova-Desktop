cmake_minimum_required(VERSION 3.10)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)


if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(NovaDesktop)

if(NOT TARGET SDL3::SDL3)
    if (NOT SDL3_FOUND)
        find_package(SDL3 QUIET)
    endif()

    # this message is generated using AI (so it could be more readable overall)
    if(NOT SDL3_FOUND)
        message(WARNING
            "\n"
            "============================================================\n"
            " SDL3 was NOT found on this system.\n"
            "\n"
            " Nova Desktop does NOT support building SDL3 via vcpkg on Linux.\n"
            "\n"
            " Please install SDL3 from your system package manager:\n"
            "   Fedora: sudo dnf install SDL3-devel\n"
            "   Arch:   sudo pacman -S sdl3\n"
            "   Ubuntu: sudo apt install libsdl3-dev\n"
            "\n"
            " Build will continue, but the application target may fail.\n"
            "============================================================\n"
        )
    endif()
else()
    message(STATUS "GE Patch has been applied")
endif()

find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

include(cmake/CPM.cmake)

include(Libs.cmake)

add_subdirectory(root/core)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_subdirectory(root/app)
    message(STATUS "[${PROJECT_NAME}] Building as standalone app -> compiling src/app")
else()
    message(STATUS "[${PROJECT_NAME}] Included as library -> skipping src/app")
endif()
