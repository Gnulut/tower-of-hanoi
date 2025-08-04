cmake_minimum_required(VERSION 4.0)
project(TowerOfHanoi)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DOWNLOAD_DEPENDENCIES "Download dependencies, currently only SDL3" False)

if (DOWNLOAD_DEPENDENCIES)
    # FetchContent downloads and configures dependencies
    include(FetchContent)
    FetchContent_Declare(
            SDL3
            GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
            GIT_TAG "main"
            EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(SDL3)
else ()
    # find_package looks for already-installed system packages.
    # Configure with `-DCMAKE_PREFIX_PATH="/path/to/package1;/path/to/package2"`
    # to add search paths.
    find_package(SDL3 CONFIG REQUIRED)
endif ()

if (ANDROID)
    # SDL applications need to be built as a shared library
    function(add_executable TARGET)
        add_library(${TARGET} SHARED ${ARGN})
    endfunction()
endif ()

add_executable(${CMAKE_PROJECT_NAME}
    src/scene/game_menu.cpp
    src/scene/main_menu.cpp
    src/scene/scene.cpp
    src/towerofhanoi/tower_data.cpp
    src/towerofhanoi/tower_disk.cpp
    src/utils/button/button_base.cpp
    src/utils/button/button_tower_height.cpp
    src/utils/color.cpp
    src/utils/draw_utils.cpp
    src/utils/random_utils.cpp
    src/config.cpp
    src/engine.cpp
    src/main.cpp
)

set_target_properties(TowerOfHanoi PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")

target_include_directories(TowerOfHanoi PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene
    ${CMAKE_CURRENT_SOURCE_DIR}/src/towerofhanoi
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/button
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3)

# This is safe to set on all platforms. Otherwise your SDL app will
#  have a terminal window pop up with it on Windows.
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)