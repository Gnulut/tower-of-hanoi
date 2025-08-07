#include "button_base.hpp"

button_base::button_base(const SDL_FRect& rect){
    this->set_rect(rect);
}

void button_base::set_rect(const SDL_FRect& rect){
    this->rect = rect;
}