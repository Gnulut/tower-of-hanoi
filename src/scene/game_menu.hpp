#pragma once

#include <SDL3/SDL.h>

#include "scene.hpp"
#include "config.hpp"
#include "tower_data.hpp"
#include "tower_GUI.hpp"
#include "draw_utils.hpp"

class game_menu_scene:public scene{
private:
    // developer settings
public:
    game_menu_scene(tower_data& tower);
    SDL_AppResult event(SDL_Event* event) override;
    void render(SDL_Renderer* renderer, SDL_Window* window) const override;
    scene* switch_scene() override;
    void reset() override;
    void resize(const int new_window_width, const int new_window_height) override;

    // link this menu to another menu
    void set_next_scene(scene* const next_scene);
    
    bool has_move() const;
    int get_move() const;
    bool get_show_target() const;

private:
    // data source
    tower_data& tower;
    tower_GUI tower_gui;

    // contains info for move action
    int move_positions[2] = {};
    int move_index = 0;

    // game runtime data
    int move_counter = 0;
    unsigned int optimal_moves = 0;
    
    // graphical data
    const float innie_rect_ratio = 0.05;
    bool show_target = true;

};