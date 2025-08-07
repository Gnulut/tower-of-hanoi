#pragma once

#include <SDL3/SDL.h>
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

    // points/unpoints this button
    void select();
    void unselect();

    bool inside(const SDL_FPoint& mouse_point);
protected:
    virtual const std::string& get_text() const = 0;

    // indicate whether this button is selected
    bool selected = false;

    // GUI location + size (rectangle)
    SDL_FRect rect;
};