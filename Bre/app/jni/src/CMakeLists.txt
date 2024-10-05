cmake_minimum_required(VERSION 3.6)

project(my_app LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure libc++ is used
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lc++_shared -latomic")

if(NOT TARGET SDL3::SDL3)
    find_package(SDL3 CONFIG)
endif()

if(NOT TARGET SDL3::SDL3)
    find_library(SDL3_LIBRARY NAMES "SDL3")
    find_path(SDL3_INCLUDE_DIR NAMES "SDL3/SDL.h")
    add_library(SDL3::SDL3 UNKNOWN IMPORTED)
    set_property(TARGET SDL3::SDL3 PROPERTY IMPORTED_LOCATION "${SDL3_LIBRARY}")
    set_property(TARGET SDL3::SDL3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${SDL3_INCLUDE_DIR}")
endif()

if(NOT TARGET SDL3::SDL3)
    message(FATAL_ERROR "Cannot find SDL3.

Possible ways to fix this:
- Use a SDL3 Android aar archive, and configure gradle to use it: prefab is required.
- Add add_subdirectory(path/to/SDL) to your CMake script, and make sure a vendored SDL is present there.
")
endif()

# Same but for SDL3_image
if(NOT TARGET SDL3_image::SDL3_image)
    find_package(SDL3_image CONFIG)
endif()

if(NOT TARGET SDL3_image::SDL3_image)
    find_library(SDL3_image_LIBRARY NAMES "SDL3_image")
    find_path(SDL3_image_INCLUDE_DIR NAMES "SDL3_image/SDL_image.h")
    add_library(SDL3_image::SDL3_image UNKNOWN IMPORTED)
    set_property(TARGET SDL3_image::SDL3_image PROPERTY IMPORTED_LOCATION "${SDL3_image_LIBRARY}")
    set_property(TARGET SDL3_image::SDL3_image PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${SDL3_image_INCLUDE_DIR}")
endif()

if(NOT TARGET SDL3_image::SDL3_image)
    message(FATAL_ERROR "Cannot find SDL3_image.")
endif()

add_library(main SHARED
        YourSourceHere.c
        Main.cpp
)
target_link_libraries(main PRIVATE SDL3::SDL3 SDL3_image::SDL3_image c++_shared atomic)
