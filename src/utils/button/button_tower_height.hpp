#pragma once

#include <SDL3/SDL.h>
#include <string>

#include "button_base.hpp"
#include "color.hpp"
#include "draw_utils.hpp"
#include "tower_data.hpp"

class button_tower_height:public button_base{
public:
    button_tower_height(const tower_data& tower);
    button_tower_height(const SDL_FRect& rect, const tower_data& tower);
    
    void extra_constructor();

    ~button_tower_height() = default;

    void render(SDL_Renderer* renderer) const override;

    void event(SDL_Event* event) override;
    // get value, used on events
    button_base::return_variant get_value() const override;

private:
// core values
    const char* button_text = "Tower height: ";
    int value = 5;

// system values
    const tower_data& tower;

// graphical values, used in rendering

    // create text for display purposes
    const std::string& get_text() const override;
    mutable std::string get_text_buffer;
    mutable int get_text_cutoff;
    
    // rectangle colors
    float border_weight_ratio = 0.10;
    float_color color_text{0.4f, 1.0f, 0.4f, 1.0f};
    float_color color_normal{0.8f, 0.3f, 0.3f, 1.0f};
    float_color color_bright{1.0f, 0.5f, 0.5f, 1.0f};
    float_color color_border{0.2f, 0.2f, 0.2f, 1.0f};
    float_color color_border_bright{0.4f, 0.3f, 0.3f, 1.0f};
    float_color color_border_select{0.3f, 0.8f, 0.5f, 1.0f};
};