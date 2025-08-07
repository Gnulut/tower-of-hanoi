#include "button_tower_height.hpp"

button_tower_height::button_tower_height(const tower_data& tower):
    tower(tower)
{
    // dont forget to set rect location when using this function
    button_tower_height::extra_constructor();
}

button_tower_height::button_tower_height(const SDL_FRect& rect, const tower_data& tower):
    tower(tower)
{
    this->set_rect(rect);
    button_tower_height::extra_constructor();
}

void button_tower_height::extra_constructor()
{
    this->get_text_buffer = this->button_text;
    this->get_text_cutoff = this->get_text_buffer.size();
}

void button_tower_height::render(SDL_Renderer* renderer) const
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
    const float scaler = 2.0;
    SDL_FRect render_rect = this->rect;
    render_rect.x += this->border_weight;
    render_rect.y += this->border_weight;
    render_rect.x/=scaler;
    render_rect.y/=scaler;
    SDL_SetRenderScale(renderer, scaler, scaler);
    SDL_SetRenderDrawColorFloat(renderer, this->color_text.red, this->color_text.green, this->color_text.blue, this->color_text.alpha);
    SDL_RenderDebugTextFormat(renderer, render_rect.x, render_rect.y, "%s", this->get_text().c_str());
    render_rect.x*=scaler;
    render_rect.y*=scaler;
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);

    if(this->selected){
        draw_outie_rectangle_weighted(renderer, this->rect, this->color_border_select, this->border_weight);
    }
}

void button_tower_height::event(SDL_Event* event)
{
    switch(event->type){
        case SDL_EVENT_KEY_DOWN:{// keyboard
            SDL_Scancode key_scancode = event->key.scancode;
            switch (key_scancode) {
                case SDL_SCANCODE_A:
                    [[fallthrough]];
                case SDL_SCANCODE_LEFT: {
                    if (this->value > 1) {
                        this->value -= 1;
                    }
                    break;
                }
                case SDL_SCANCODE_D:
                    [[fallthrough]];
                case SDL_SCANCODE_RIGHT: {
                    if (this->value < this->tower.get_max_height()) {
                        this->value += 1;
                    }
                    break;
                }
                default:{break;}
            }
            break;
        }
        default:{break;}
    }
}

button_base::return_variant button_tower_height::get_value() const
{
    return this->value;
}

const std::string& button_tower_height::get_text() const
{
    if(this->get_text_cutoff < this->get_text_buffer.size()){
        this->get_text_buffer.erase(this->get_text_cutoff);
    }
    this->get_text_buffer += std::to_string(this->value);
    return this->get_text_buffer;
}





