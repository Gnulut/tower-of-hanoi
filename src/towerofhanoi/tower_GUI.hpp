#pragma once

#include<SDL3/SDL.h>

#include "tower_data.hpp"
#include "draw_utils.hpp"
class game_menu_scene;

class tower_GUI{
public:
    tower_GUI(tower_data& tower, game_menu_scene* game_menu);
    ~tower_GUI() = default;
    
    // renders the tower
    void render(SDL_Renderer* renderer, SDL_Window* window) const;

    // should be called on window resize, readjust sizes for GUI items
    void resize(const int new_window_width, const int new_window_height);

    // get one peg's width
    float get_width() const;

private:
    // main data source
    tower_data& tower;
    game_menu_scene* game_menu;

    SDL_FRect* make_disk_rect(const tower_disk& disk) const;

    // graphical data
    int window_width, window_height;
    float peg_width;
    float minor_disk_width;
    float disk_height;
    const float innie_rect_ratio = 0.05;
};