#pragma once

#include <variant>

#include "tower_data.hpp"

class button_base{
public:
    button_base() = default;
    button_base(const SDL_FRect& rect);

    ~button_base() = default;

    // render button
    virtual void render(SDL_Renderer* renderer) const = 0;
    
    // return button values
    using return_variant = std::variant<int, start_or_target_position>;
    virtual return_variant get_value() const = 0;

    // event handling
    virtual void event(SDL_Event* event) = 0;

    
    // setup rect graphical (GUI) location
    void set_rect(const SDL_FRect& rect);

protected:
    virtual const std::string& get_text() const = 0;
    // GUI location + size (rectangle)
    SDL_FRect rect;
};