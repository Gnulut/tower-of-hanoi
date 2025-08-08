#include "tower_GUI.hpp"
#include "game_menu.hpp"

tower_GUI::tower_GUI(tower_data& tower, game_menu_scene* game_menu):
    tower(tower), game_menu(game_menu)
{
    
}

void tower_GUI::render(SDL_Renderer* renderer, SDL_Window* window) const
{
    const int tower_height = this->tower.get_height();
    {// render current_tower
        for (int tower_position = 0; tower_position < this->tower.get_width(); ++tower_position){
            for (auto& disk: this->tower.view_peg(tower_position)){
                // create rect
                SDL_FRect* rect = tower_GUI::make_disk_rect(*disk);
                
                // put rect
                const float_color& color = disk->get_color();
                SDL_SetRenderDrawColorFloat(renderer, color.red, color.green, color.blue, color.alpha);
                SDL_RenderFillRect(renderer, rect);
                
                // memory release
                delete rect;
            }
        }
    }// endof render current_tower

    if(this->game_menu->get_show_target()){// render target tower
        // std::array<tower_disk>, it will be array, data inside may have different 
        const tower_disk* targets = this->tower.view_target();
        for(int i=0; i < this->tower.get_height(); ++i){
            const tower_disk* disk = &targets[i];

            // create rect
            SDL_FRect* rect = tower_GUI::make_disk_rect(*disk);

            // put rect, different from  actual disk implementation
            int location_horizontal = disk->get_horizontal();
            int location_vertical = disk->get_vertical();
            // if target is on empty space or size doesn't match
            if(this->tower.view_peg(location_horizontal).size() <= location_vertical ||
               this->tower.view_peg(location_horizontal)[location_vertical]->get_size() != disk->get_size())
            { // red color
                draw_innie_rectangle_weighted(renderer, *rect, 1.0f, 0.f, 0.2f, 0.25f, 
                    (float)(this->innie_rect_ratio*std::min(rect->w, rect->h)));
            }
            // otherwise target is achieved
            else{ // green color
                draw_innie_rectangle_weighted(renderer, *rect, 0.f, 1.0f, 0.2f, 0.25f, 
                    (float)(this->innie_rect_ratio*std::min(rect->w, rect->h)));
            }

            // release memory
            delete rect;
        }
    }
    // render selected disk
    
    if(this->game_menu->has_move()){// has player selection
        // selection
        int location_horizontal = this->game_menu->get_move();

        // check availability
        if(!this->tower.view_peg(location_horizontal).empty()){// have disk
            // get disk
            const tower_disk* disk = this->tower.view_peg(location_horizontal).back();

            // get rect
            SDL_FRect* rect = this->make_disk_rect(*disk);

            // put rect
            draw_innie_rectangle_weighted(renderer, *rect, 1.0f, 1.0f, 0.2f, SDL_ALPHA_OPAQUE_FLOAT, (float)(this->innie_rect_ratio*std::min(rect->w, rect->h)));

            // release memory
            delete rect;
        }else{// no disk
            // get rect
            SDL_FRect rect{(float) location_horizontal * (float) constants::START_WINDOW_WIDTH / (float) this->tower.get_width(), 0.f, 
                           (float) constants::START_WINDOW_WIDTH / (float) this->tower.get_width(), constants::START_WINDOW_HEIGHT};
            // put rect
            draw_innie_rectangle_weighted(renderer, rect, 1.0f, 1.0f, 0.2f, SDL_ALPHA_OPAQUE_FLOAT, (float)(this->innie_rect_ratio*std::min(rect.w, rect.h)));
        }
    }
}

void tower_GUI::resize(const int new_window_width, const int new_window_height)
{
    this->window_width = new_window_width;
    this->window_height = new_window_height;
    this->peg_width = (float) this->window_width / (float) this->tower.get_width();
    this->minor_disk_width = this->peg_width / (float) this->tower.get_height();
    this->disk_height = (float) this->window_height / (float) this->tower.get_height();
}

SDL_FRect* tower_GUI::make_disk_rect(const tower_disk& disk) const
{
    // in pixels
    double disk_width = this->minor_disk_width * (double) disk.get_size();
    return new SDL_FRect{
                (float)(this->window_width * ((float)disk.get_horizontal() + 0.5f) / this->tower.get_width() - (disk_width * 0.5f)),
                (float)(this->window_height - this->disk_height * (disk.get_vertical() + 1)),
                (float)disk_width, 
                (float)this->disk_height
                };
}

float tower_GUI::get_width() const
{
    return this->peg_width;
}