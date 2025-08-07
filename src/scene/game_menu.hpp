#pragma once

#include <SDL3/SDL.h>

#include "scene.hpp"
#include "config.hpp"
#include "tower_data.hpp"
#include "draw_utils.hpp"

class game_menu_scene:public scene{
private:
    // developer settings
    const double innie_rect_ratio = 0.05;
public:
    game_menu_scene(tower_data& tower);

    SDL_AppResult event(SDL_Event* event) override;

    void render(SDL_Renderer* renderer) override;

    scene* switch_scene() override;

    void reset() override;

    // link this menu to another menu
    void set_next_scene(scene* next_scene);

protected:
    // create new rect (heap) which represent its GUI position
    SDL_FRect* make_disk_rect(const tower_disk& disk);
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
    double peg_width;
    double minor_disk_width;
    double disk_height;
};