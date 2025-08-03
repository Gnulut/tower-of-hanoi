#include "main_menu.hpp"

main_menu_scene::main_menu_scene(tower_data& tower):
    tower(tower)
{
}

SDL_AppResult main_menu_scene::event(SDL_Event *event) {
    switch(event->type){
        case SDL_EVENT_KEY_DOWN:{// keyboard
            SDL_Scancode key_scancode = event->key.scancode;
            switch (key_scancode) {
                case SDL_SCANCODE_RETURN:{
                    if (this->current_button_selected == 3) {
                        tower.new_game(button_options[0], static_cast<start_or_target_position>(button_options[1]), static_cast<start_or_target_position>(button_options[2]));
                        this->switch_scene_flag=true;
                    }
                    break;
                } 
                case SDL_SCANCODE_UP: {
                    current_button_selected = (current_button_selected + 3)%4;
                    break;
                }
                case SDL_SCANCODE_DOWN: {
                    current_button_selected = (current_button_selected + 1)%4;
                    break;
                }
                case SDL_SCANCODE_LEFT: {
                    if (current_button_selected == 0) {
                        if (this->button_options[0] > 1) {
                            this->button_options[0] -= 1;
                        }
                    }
                    else if (current_button_selected == 1) {
                        do {
                            button_options[1] = (button_options[1] + 3)%4;
                        }while(button_options[1] == button_options[2] && button_options[1] != 3);
                    }
                    else if (current_button_selected == 2) {
                        do {
                            button_options[2] = (button_options[2] + 3) % 4;
                        } while (button_options[1] == button_options[2] && button_options[2] != 3);
                    }
                    break;
                }
                case SDL_SCANCODE_RIGHT: {
                    if (current_button_selected == 0) {
                        if (this->button_options[0] < this->tower.get_max_height()) {
                            this->button_options[0] += 1;
                        }
                    }
                    else if (current_button_selected == 1) {
                        do {
                            button_options[1] = (button_options[1] + 1) % 4;
                        } while (button_options[1] == button_options[2] && button_options[1] != 3);
                    }
                    else if (current_button_selected == 2) {
                        do {
                            button_options[2] = (button_options[2] + 1) % 4;
                        } while (button_options[1] == button_options[2] && button_options[2] != 3);
                    }
                    break;
                }
                default:{
                    break;
                }
            }
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_DOWN:{
            if ((int)event->button.button == SDL_BUTTON_LEFT) {
                float mouse_x = event->button.x, mouse_y = event->button.y;
                // get x_left_bound, x_right_bound;
                double left_bound = (constants::WINDOW_WIDTH * (1.0 - this->button_width_ratio)) / 2.0;
                double right_bound = (constants::WINDOW_WIDTH * (1.0 + this->button_width_ratio)) / 2.0;
                if (mouse_x<left_bound || mouse_x>right_bound) {
                    break;
                }
                // get each rectangle y_top_bound, y_bottom_bound
                double each_button_height = (double) constants::WINDOW_HEIGHT / this->button_count;// single button size, includes padding
                int button_number = (int) (mouse_y/each_button_height);
                this->current_button_selected = button_number;
                
                if(event->button.clicks >= 2){
                    if (this->current_button_selected == 3) {
                        tower.new_game(button_options[0], static_cast<start_or_target_position>(button_options[1]), static_cast<start_or_target_position>(button_options[2]));
                        this->switch_scene_flag=true;
                    }
                }
            }
            break;
        }
        default:{
            // intentionally empty, represents unconfigured event
            break;
        }
    }
    return SDL_APP_CONTINUE;
}

void main_menu_scene::render(SDL_Renderer *renderer){
    // IDEA : tower height, start_position, goal_position (on random, largest block always different), start
    double each_button_height = (double) constants::WINDOW_HEIGHT / button_count;// single button size, includes padding
    double vertical_padding_ratio = 0.05; // [0.0,0.5), 0.5>= will have 0 block size
    double each_padding_height = each_button_height * vertical_padding_ratio;// paddings
    double each_height_no_padding = each_button_height - (2 * each_padding_height);// inner rect
    
    
    {// displaying buttons
        double padding_start_y = 0;
        double button_start_y = padding_start_y + each_padding_height;
        double button_width = constants::WINDOW_WIDTH * button_width_ratio;
        double start_x = (constants::WINDOW_WIDTH - button_width)/2.0; // same as: window_width/2 - rectangle_width/2
        SDL_FRect rect{(float)start_x, (float)button_start_y, (float)button_width, (float)each_height_no_padding};

        int r = 200, g = 50, b = 200; // initial color choice, for debugging/development purposes, final version may use other;
        int text_r = 200, text_g = 200, text_b = 50;
        for (int button_number = 0; button_number < button_count; ++button_number) {
            SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
            
            
            if (button_number == current_button_selected) {
                //SDL_SetRenderDrawColor(renderer, 100, 100, 200, SDL_ALPHA_OPAQUE);
                //SDL_RenderRect(renderer, &rect);
                draw_outie_rectangle_weighted(renderer, &rect, 0.4f, 0.4f, 0.8f, SDL_ALPHA_OPAQUE_FLOAT, (float) each_padding_height);
            }

            SDL_SetRenderDrawColor(renderer, text_r, text_g, text_b, SDL_ALPHA_OPAQUE);
            const float scaler = 2.0;
            rect.x/=scaler;
            rect.y/=scaler;
            SDL_SetRenderScale(renderer, scaler, scaler);
            if (button_number == 0) {
                SDL_RenderDebugTextFormat(renderer, rect.x, rect.y, "%s%s",
                    button_texts[button_number], std::to_string(button_options[button_number]).c_str());
            }
            else if (button_number <= 2) {
                SDL_RenderDebugTextFormat(renderer, rect.x, rect.y, "%s%s",
                    button_texts[button_number], position_texts[button_options[button_number]]);
            }
            else {
                SDL_RenderDebugText(renderer, rect.x, rect.y, button_texts[button_number]);
            }
            rect.x*=scaler;
            rect.y*=scaler;
            SDL_SetRenderScale(renderer, 1.0f, 1.0f);
            //next iteration
            rect.y = (float) (button_start_y += each_button_height);
        }
    }
}

scene* main_menu_scene::switch_scene(){
    // for now only simple scene switch, same as all other scene, when scenes has branching it iwll differ
    if(this->switch_scene_flag){
        this->switch_scene_flag=false;
        this->next_scene->reset();
        return this->next_scene;
    }else{
        return this;
    }
}

void main_menu_scene::set_next_scene(scene* next_scene){
    this->next_scene = next_scene;
}

void main_menu_scene::reset(){
    
}