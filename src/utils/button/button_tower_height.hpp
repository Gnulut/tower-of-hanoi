#pragma once

#include <SDL3/SDL.h>

#include "button_base.hpp"
#include "color.hpp"
#include "draw_utils.hpp"

class button_tower_height:public button_base{
public:
    button_tower_height();

    button_tower_height(const SDL_FRect& rect);

    ~button_tower_height() = default;

    void render(SDL_Renderer* renderer) override;

    // get value, used on events
    button_base::return_variant get_value() override;

    // setup rect graphical (GUI) location
    void set_rect(const SDL_FRect& rect) override;

private:
// core values
    const char* button_text = "Tower height: ";
    int value = 5;

// graphical values, used in rendering
    float border_weight = 30; // in pixels
    float_color color_normal{0.8f, 0.0f, 0.0f, 1.0f};
    float_color color_bright{1.0f, 0.2f, 0.2f, 1.0f};
    float_color color_border{0.0f, 0.0f, 0.0f, 1.0f};
    float_color color_border_bright{0.2f, 0.2f, 0.2f, 1.0f};
    SDL_FRect rect;
};