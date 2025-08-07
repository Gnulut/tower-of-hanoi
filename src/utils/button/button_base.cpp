#include "button_base.hpp"

button_base::button_base(const SDL_FRect& rect)
{
    this->set_rect(rect);
}

void button_base::set_rect(const SDL_FRect& rect)
{
    this->rect = rect;
}

void button_base::select()
{
    this->selected = true;
}

void button_base::unselect()
{
    this->selected = false;
}

bool button_base::inside(const SDL_FPoint& mouse_point)
{
    return SDL_PointInRectFloat(&mouse_point, &this->rect);
    // return this->rect.x <= mouse_point.x && mouse_point.x <= this->rect.x + this->rect.w &&
    //        this->rect.y <= mouse_point.y && mouse_point.y <= this->rect.y + this->rect.h;
}