#pragma once

#include <variant>

#include "tower_data.hpp"

class button_base{
public:
    button_base() = default;

    ~button_base() = default;

    virtual void render(SDL_Renderer* renderer) = 0;
    
    using return_variant = std::variant<int, start_or_target_position>;
    virtual return_variant get_value() = 0;

    virtual void set_rect(const SDL_FRect& rect) = 0;
};