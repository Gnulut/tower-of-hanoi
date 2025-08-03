#pragma once

#include <SDL3/SDL.h>
#include <string>

#include "tower_data.hpp"
#include "draw_utils.hpp"
#include "config.hpp"
#include "scene.hpp"

class engine {
private:
    tower_data tower;
    scene* current_scene;
    int current_button_selected = 0;

    // Button texts and positions
    // const char* const button_texts[4] {"Tower Height: ", "Start Position: ", "Goal Position: ", "Start: "};
    // const char* const position_texts[4] = {"Left", "Middle", "Right", "Random"};
    // int button_options[3] = {5, 0, 2};
    // double button_width_ratio = 0.3;// ratio of button to WINDOW_WIDTH;
    // int button_count = 4;

    // For tower_event_handler
    int move_positions[2] = {};
    int move_index = 0;


public:
    SDL_Window* window = nullptr;   // standard SDL usage
    SDL_Renderer* renderer = nullptr;

    engine();

    // Core functions
    void render();

    // Event handlers
    SDL_AppResult event(SDL_Event* event);

    void try_switch();

    tower_data& get_tower();

    void set_first_scene(scene* first_scene);
};
