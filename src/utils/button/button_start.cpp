#include "button_start.hpp"
#include "main_menu.hpp"

button_start::button_start()
{
    button_start::extra_constructor();
}

button_start::button_start(const SDL_FRect& rect)
{
    this->set_rect(rect);
    button_start::extra_constructor();
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

    float border_weight = this->border_weight_ratio*std::min(this->rect.h, this->rect.w);

    // mouse hover
    if(SDL_PointInRectFloat(&mouse_point, &this->rect)){
        draw_bordered_rectangle_weighted(renderer, this->rect, this->color_bright, this->color_border_bright, border_weight);
    }
    // mouse not hover
    else{
        draw_bordered_rectangle_weighted(renderer, this->rect, this->color_normal, this->color_border, border_weight);
    }
    const float scaler = 2.0;
    SDL_FRect render_rect = this->rect;
    
    render_rect.x += border_weight;
    render_rect.y += border_weight;
    render_rect.x/=scaler;
    render_rect.y/=scaler;
    SDL_SetRenderScale(renderer, scaler, scaler);
    SDL_SetRenderDrawColorFloat(renderer, this->color_text.red, this->color_text.green, this->color_text.blue, this->color_text.alpha);
    SDL_RenderDebugTextFormat(renderer, render_rect.x, render_rect.y, "%s", this->get_text().c_str());
    render_rect.x*=scaler;
    render_rect.y*=scaler;
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);

    if(this->selected){
        draw_outie_rectangle_weighted(renderer, this->rect, this->color_border_select, border_weight);
    }
}

void button_start::event(SDL_Event* event)
{
    switch(event->type){
        case SDL_EVENT_KEY_DOWN:{
            switch(event->key.scancode){
                case SDL_SCANCODE_RETURN:{
                    this->signal_start();
                }
            }
        }
    }
}

button_base::return_variant button_start::get_value() const
{
    return 0;
}

void button_start::link_menu(main_menu_scene* main_menu)
{
    this->main_menu = main_menu;
}

const std::string& button_start::get_text() const
{
    return this->get_text_buffer;
}

void button_start::signal_start()
{
    this->main_menu->change_scene();
}
