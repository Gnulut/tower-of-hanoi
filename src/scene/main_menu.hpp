#pragma once

#include <SDL3/SDL.h>
#include <string>

#include "scene.hpp"
#include "config.hpp"
#include "draw_utils.hpp"
#include "tower_data.hpp"

class main_menu_scene : public scene{
public:
    main_menu_scene(tower_data& tower);
    SDL_AppResult event(SDL_Event* event) override;
    void render(SDL_Renderer* renderer) override;
    scene* switch_scene() override;
    void main_menu_scene::reset() override;
    void set_next_scene(scene* next_scene);
private:
    //position of button
    int current_button_selected = 0;
    const char* const button_texts[4] {"Tower Height: ", "Start Position: ", "Goal Position: ", "Start"};
    const char* const position_texts[4] = {"Left", "Middle", "Right", "Random"};
    int button_options[3] = {5, 0, 2};
    double button_width_ratio = 0.3;// ratio of button to WINDOW_WIDTH;
    int button_count = 4;

    tower_data &tower;
};