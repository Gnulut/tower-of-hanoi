#include "button_tower_height.hpp"

button_tower_height::button_tower_height() {

}

button_tower_height::button_tower_height(const SDL_FRect& rect) {
    this->set_rect(rect);
}

void button_tower_height::render(SDL_Renderer* renderer) {
    SDL_FPoint mouse_point;
    SDL_GetMouseState(&mouse_point.x, &mouse_point.y);

    // mouse hover
    if(SDL_PointInRectFloat(&mouse_point, &this->rect)){
        draw_bordered_rectangle_weighted(renderer, this->rect, this->color_bright, this->color_border_bright, this->border_weight);
    }
    // mouse not hover
    else{
        draw_bordered_rectangle_weighted(renderer, this->rect, this->color_normal, this->color_border, this->border_weight);
    }
}

button_base::return_variant button_tower_height::get_value() {
    return this->value;
}

void button_tower_height::set_rect(const SDL_FRect& rect) {
    this->rect = rect;
}

