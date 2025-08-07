#include "button_start.hpp"

button_start::button_start()
{

}

button_start::button_start(const SDL_FRect& rect)
{
    this->set_rect(rect);
}

void button_start::extra_constructor()
{
    this->get_text_buffer = this->button_text;
    this->get_text_cutoff = this->get_text_buffer.size();
}

void button_start::render(SDL_Renderer* renderer) const
{
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

void button_start::event(SDL_Event* event)
{
    
}

button_base::return_variant button_start::get_value() const
{
    return 0;
}

const std::string& button_start::get_text() const
{
    return this->get_text_buffer;
}

