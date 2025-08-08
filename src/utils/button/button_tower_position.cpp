#include "button_tower_position.hpp"

button_tower_position::button_tower_position()
{
    button_tower_position::extra_constructor();
}

button_tower_position::button_tower_position(const SDL_FRect& rect)
{
    this->set_rect(rect);
    button_tower_position::extra_constructor();
}

void button_tower_position::extra_constructor()
{
    if(type < 2){
        this->button_text = button_tower_position::button_texts[button_tower_position::type];
        this->value = button_tower_position::default_positions[button_tower_position::type];
        this->value_text = button_tower_position::texts[static_cast<int>(this->value)];
        button_tower_position::type += 1;
        this->get_text_buffer = this->button_text;
        this->get_text_cutoff = (int)this->get_text_buffer.size();
    }else{
        SDL_Log("Excessive amount of button_tower_position detected");
        // this shouldn't happen, will cause problems
    }
}

void button_tower_position::render(SDL_Renderer* renderer) const
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

void button_tower_position::event(SDL_Event* event)
{
    switch(event->type) {
        case SDL_EVENT_KEY_DOWN: {// keyboard
            SDL_Scancode key_scancode = event->key.scancode;
            switch (key_scancode) {
                case SDL_SCANCODE_A:
                    [[fallthrough]];
                case SDL_SCANCODE_LEFT: {
                    do{
                        this->value = (start_or_target_position) (((int)this->value + 3)%4);
                    }while(this->value==std::get<start_or_target_position>(this->neighbour->get_value()) &&
                           this->value!=start_or_target_position::RANDOM);
                    this->value_text = button_tower_position::texts[static_cast<int>(this->value)];
                    break;
                }
                case SDL_SCANCODE_D:
                    [[fallthrough]];
                case SDL_SCANCODE_RIGHT: {
                    do{
                        this->value = (start_or_target_position) (((int)this->value + 1)%4);
                    }while(this->value == std::get<start_or_target_position>(this->neighbour->get_value()) &&
                           this->value != start_or_target_position::RANDOM);
                    this->value_text = button_tower_position::texts[static_cast<int>(this->value)];
                    break;
                }
                default:{break;}
            }
            break;
        }
        default:{break;}
    }
}

button_base::return_variant button_tower_position::get_value() const
{
    return this->value;
}

void button_tower_position::set_neighbour(const button_tower_position* const neighbour)
{   
    this->neighbour = neighbour;
}

const std::string& button_tower_position::get_text() const
{
    if(this->get_text_cutoff < this->get_text_buffer.size()){
        this->get_text_buffer.erase(this->get_text_cutoff);
    }
    this->get_text_buffer += value_text;
    return this->get_text_buffer;
}




