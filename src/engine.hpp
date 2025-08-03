#pragma once

#include <SDL3/SDL.h>
#include <string>

#include "tower_data.hpp"
#include "config.hpp"
#include "main_menu.hpp"
#include "game_menu.hpp"

class engine {
public:
    engine();
    ~engine();

// core function(s)

    // render
    void render();

    // Event handlers
    SDL_AppResult event(SDL_Event* event);

    // change scene
    void try_switch();

// misc function(s)

    // get_window
    SDL_Window*& get_window();

    // get_renderer
    SDL_Renderer*& get_renderer();

    // let others borrow tower
    tower_data& get_tower();

    // link up first scene, usually it's main menu
    void set_first_scene(scene* first_scene);

// need to delete variables

    void add_scene(scene* new_scene);

private:
// window and renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

// system data
    tower_data tower;
    scene* current_scene = nullptr;
    std::vector<scene*> scenes;
};
