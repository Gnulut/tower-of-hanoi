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
    void render(SDL_Renderer* renderer, SDL_Window* window) const override;
    scene* switch_scene() override;
    void reset() override;
    void resize(const int new_window_width, const int new_window_height) override;

    // link up transition scene
    void set_next_scene(scene* const next_scene);

    void change_scene();
private:
    // buttons
    int current_button_selected = 0;
    int button_count = 4;
    button_tower_height tower_height_button;
    button_tower_position tower_start_position_button;
    button_tower_position tower_target_position_button;
    button_start tower_start_button;
    const int tower_height_button_index = 0;
    const int tower_start_position_index = 1;
    const int tower_target_position_index = 2;
    const int tower_start_button_index = 3;
    button_base* buttons[4];

    // tower
    tower_data &tower;
};