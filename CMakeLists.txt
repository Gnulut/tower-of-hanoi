cmake_minimum_required(VERSION 3.16)
project(TowerOfHanoi)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
  
  # Pass Emscripten-specific flags to generate a runnable HTML page
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sEXIT_RUNTIME=1 -sWASM=1 --shell-file ${CMAKE_SOURCE_DIR}/shell.html")
endif()

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

# if(NOT EMSCRIPTEN)
#     set_target_properties(TowerOfHanoi PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
# endif()

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene
    ${CMAKE_CURRENT_SOURCE_DIR}/src/towerofhanoi
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/button
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3)

# This is safe to set on all platforms. Otherwise your SDL app will
#  have a terminal window pop up with it on Windows.
# set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)