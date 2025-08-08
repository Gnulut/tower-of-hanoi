#pragma once

#include <SDL3/SDL.h>

#include "scene.hpp"
#include "config.hpp"
#include "tower_data.hpp"
#include "draw_utils.hpp"

class game_menu_scene:public scene{
private:
    // developer settings
    const float innie_rect_ratio = 0.05;
public:
    game_menu_scene(tower_data& tower);
    SDL_AppResult event(SDL_Event* event) override;
    void render(SDL_Renderer* renderer, SDL_Window* window) const override;
    scene* switch_scene() override;
    void reset() override;
    void resize(const int new_window_width, const int new_window_height) override;

    // link this menu to another menu
    void set_next_scene(scene* const next_scene);

protected:
    // create new rect (heap) which represent its GUI position
    SDL_FRect* make_disk_rect(const tower_disk& disk) const;
private:
    // data source
    tower_data& tower;

    // contains info for move action
    int move_positions[2] = {};
    int move_index = 0;

    // game runtime data
    int move_counter = 0;
    unsigned int optimal_moves = 0;
    
    // graphical data
    float peg_width;
    float minor_disk_width;
    float disk_height;
};