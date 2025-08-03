#include "game_menu.hpp"

game_menu_scene::game_menu_scene(tower_data& tower)
    :tower(tower)
{
    reset();
}

SDL_AppResult game_menu_scene::event(SDL_Event* event) {
    switch(event->type){
        // keyboard down
        case SDL_EVENT_KEY_DOWN:{
            SDL_Scancode key_scancode = event->key.scancode;
            switch(key_scancode){
                case SDL_SCANCODE_ESCAPE:{
                    this->switch_scene_flag = true;
                    break;
                }
                case SDL_SCANCODE_R:{
                    this->tower.reset_start();
                    this->move_counter = 0;
                    this->move_index = 0;
                    break;
                }
            }
            break;
        }
        // mouse down
        case SDL_EVENT_MOUSE_BUTTON_DOWN:{
            if ((int)event->button.button == 1){
                float mouse_x = event->button.x;
                // unused mouse_y
                //float mouse_y = event->button.y;

                // number of pegs, in normal ToH(Tower of Hanoi) it's 3
                const int tower_width = this->tower.get_width();

                // deduce which peg is chosen
                double peg_width = (double)constants::WINDOW_WIDTH / tower_width;
                int tower_position = (int)(mouse_x / peg_width);
                // new move
                if (this->move_index == 0){
                    this->move_positions[this->move_index] = tower_position;
                    this->move_index++;
                }
                // existing move
                else{
                    // cancel move
                    if(this->move_positions[0] == tower_position){
                        this->move_index--;
                    }
                    // do move, and reset move counter
                    else{
                        this->move_positions[1] = tower_position;
                        this->tower.move(this->move_positions[0], this->move_positions[1]);
                        this->move_counter++;
                        this->move_index = 0;
                    }
                }
            }
            break;
        }
        // others
        default:{
            //intentionally left empty
            break;
        }
    }
    return SDL_APP_CONTINUE;
}

void game_menu_scene::render(SDL_Renderer* renderer) {
    const int tower_height = this->tower.get_height();
    {// render current_tower
        for (int tower_position = 0; tower_position < this->tower.get_width(); ++tower_position){
            for (auto& disk: this->tower.view_peg(tower_position)){
                // create rect
                SDL_FRect* rect = game_menu_scene::make_disk_rect(*disk);
                
                // put rect
                const float_color& color = disk->get_color();
                SDL_SetRenderDrawColorFloat(renderer, color.red, color.green, color.blue, color.alpha);
                SDL_RenderFillRect(renderer, rect);
                
                // memory release
                delete rect;
            }
        }
    }// endof render current_tower

    {// render target tower
        // std::array<tower_disk>, it will be array, data inside may have different 
        const tower_disk* targets = this->tower.view_target();
        for(int i=0; i < this->tower.get_height(); ++i){
            const tower_disk* disk = &targets[i];

            // create rect
            SDL_FRect* rect = game_menu_scene::make_disk_rect(*disk);

            // put rect, different from  actual disk implementation
            int location_horizontal = disk->get_horizontal();
            int location_vertical = disk->get_vertical();
            // if target is on empty space or size doesn't match
            if(this->tower.view_peg(location_horizontal).size() <= location_vertical ||
               this->tower.view_peg(location_horizontal)[location_vertical]->get_size() != disk->get_size())
            { // red color
                draw_innie_rectangle_weighted(renderer, rect, 1.0f, 0.f, 0.2f, 0.25f, 
                    (float)(this->innie_rect_ratio*std::min(rect->w, rect->h)));
            }
            // otherwise target is achieved
            else{ // green color
                draw_innie_rectangle_weighted(renderer, rect, 0.f, 1.0f, 0.2f, 0.25f, 
                    (float)(this->innie_rect_ratio*std::min(rect->w, rect->h)));
            }

            // release memory
            delete rect;
        }
    }
    // render selected disk
    if(this->move_index == 1){// has player selection
        // selection
        int location_horizontal = this->move_positions[0];

        // check availability
        if(!this->tower.view_peg(location_horizontal).empty()){// have disk
            // get disk
            const tower_disk* disk = this->tower.view_peg(location_horizontal).back();

            // get rect
            SDL_FRect* rect = game_menu_scene::make_disk_rect(*disk);

            // put rect
            draw_innie_rectangle_weighted(renderer, rect, 1.0f, 1.0f, 0.2f, SDL_ALPHA_OPAQUE_FLOAT, (float)(this->innie_rect_ratio*std::min(rect->w, rect->h)));

            // release memory
            delete rect;
        }else{// no disk
            // get rect
            SDL_FRect rect{(float) location_horizontal * (float) constants::WINDOW_WIDTH / (float) this->tower.get_width(), 0.f, 
                           (float) constants::WINDOW_WIDTH / (float) this->tower.get_width(), constants::WINDOW_HEIGHT};
            // put rect
            draw_innie_rectangle_weighted(renderer, &rect, 1.0f, 1.0f, 0.2f, SDL_ALPHA_OPAQUE_FLOAT, (float)(this->innie_rect_ratio*std::min(rect.w, rect.h)));
        }
    }

    // render move counter
    SDL_SetRenderScale(renderer, 4.0f, 4.0f);
    SDL_SetRenderDrawColorFloat(renderer, 0.1f, 0.5f, 1.0f, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderDebugTextFormat(renderer, 0.f, 0.f, "Optimal Moves: %d", this->optimal_moves);
    SDL_RenderDebugTextFormat(renderer, 0.f, 10.f, "Moves: %d", this->move_counter);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

scene* game_menu_scene::switch_scene(){
    // for now only simple scene switch, same as all other scene, when scenes has branching it will differ
    if(this->switch_scene_flag){
        this->switch_scene_flag=false;
        return this->next_scene;
    }else{
        return this;
    }
}

void game_menu_scene::set_next_scene(scene* next_scene){
    this->next_scene = next_scene;
}

void game_menu_scene::reset(){
    this->peg_width = (double) constants::WINDOW_WIDTH / this->tower.get_width();
    this->minor_disk_width = this->peg_width / (double) this->tower.get_height();
    this->disk_height = (double) constants::WINDOW_HEIGHT / (double) this->tower.get_height();
    this->optimal_moves = this->tower.get_optimal();
    this->move_counter = 0;
}

SDL_FRect* game_menu_scene::make_disk_rect(const tower_disk& disk){
    // in pixels
    double disk_width = this->minor_disk_width * (double) disk.get_size();
    return new SDL_FRect{
                (float)(constants::WINDOW_WIDTH * (disk.get_horizontal() + 0.5) / this->tower.get_width() - (disk_width * 0.5)),
                (float)(constants::WINDOW_HEIGHT - this->disk_height * (disk.get_vertical() + 1)),
                (float)disk_width, 
                (float)this->disk_height
                };
}
