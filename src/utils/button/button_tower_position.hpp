#pragma once

#include <SDL3/SDL.h>
#include <variant>
#include <string>

#include "button_base.hpp"
#include "color.hpp"
#include "draw_utils.hpp"
#include "tower_data.hpp"
#include <iostream>

class button_tower_position:public button_base{
public:
    button_tower_position();
    button_tower_position(const SDL_FRect& rect);
    
    void extra_constructor();

    ~button_tower_position() = default;

    void render(SDL_Renderer* renderer) const override;

    void event(SDL_Event* event);
    // get value, used on events
    button_base::return_variant get_value() const override;

    // create neighbour, needed to prevent same values
    void set_neighbour(const button_tower_position* const neighbour);

private:
// core values
    const char* button_text;
    start_or_target_position value;
    const char* value_text;
// system values
    const button_tower_position* neighbour;

    // control whether this is a start tower or a target tower
    inline static const char* button_texts[2] = {"Start Position: ", "Target Position: "};
    inline static start_or_target_position default_positions[2] = {start_or_target_position::LEFT, start_or_target_position::RIGHT};
    inline static const char* texts[4] = {"Left", "Middle", "Right", "Random"};
    inline static int type = 0;

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