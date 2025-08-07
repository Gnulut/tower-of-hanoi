#pragma once

#include <SDL3/SDL.h>
#include <string>

#include "scene.hpp"
#include "config.hpp"
#include "draw_utils.hpp"
#include "tower_data.hpp"
#include "button_base.hpp"
#include "button_tower_height.hpp"
#include "button_tower_position.hpp"
#include "button_start.hpp"

class main_menu_scene : public scene{
public:
    main_menu_scene(tower_data& tower);
    ~main_menu_scene();
    SDL_AppResult event(SDL_Event* event) override;
    void render(SDL_Renderer* renderer) override;
    scene* switch_scene() override;
    void reset() override;

    // link up transition scene
    void set_next_scene(scene* next_scene);

    void change_scene();
private:
    // buttons
    int current_button_selected = 0;
    int button_count = 4;
    button_base* buttons[4];

    const int tower_height_button_index = 0;
    const int tower_start_position_index = 1;
    const int tower_target_position_index = 2;
    const int start_button_index = 3;

    // tower
    tower_data &tower;
};