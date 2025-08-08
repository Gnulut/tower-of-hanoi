#include "game_menu.hpp"

game_menu_scene::game_menu_scene(tower_data& tower):
    tower(tower), tower_gui(tower, this)
{
    reset();
}

SDL_AppResult game_menu_scene::event(SDL_Event* event)
{
    switch(event->type) {
        case SDL_EVENT_KEY_DOWN: {// keyboard down
            SDL_Scancode key_scancode = event->key.scancode;
            switch(key_scancode){
                case SDL_SCANCODE_ESCAPE: { //  go back to main menu
                    this->switch_scene_flag = true;
                    break;
                }
                case SDL_SCANCODE_R: { // reset
                    this->reset();
                    break;
                }
                case SDL_SCANCODE_T: { // toggle show target behavior (show/no show)
                    this->show_target = !this->show_target;
                    break;
                } 
                default:{break;}
            }
            break;
        }
        
        case SDL_EVENT_MOUSE_BUTTON_DOWN: { // mouse down
            if ((int)event->button.button == 1){
                float mouse_x = event->button.x;
                // unused mouse_y
                //float mouse_y = event->button.y;

                // number of pegs, in normal ToH(Tower of Hanoi) it's 3
                const int tower_width = this->tower.get_width();

                // deduce which peg is chosen
                int tower_position = (int)(mouse_x / this->tower_gui.get_width());
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
        default:{break;}
    }
    return SDL_APP_CONTINUE;
}

void game_menu_scene::render(SDL_Renderer* renderer, SDL_Window* window) const
{
    // tower main graphics
    this->tower_gui.render(renderer, window);

    // render move counter
    SDL_SetRenderScale(renderer, 4.0f, 4.0f);
    SDL_SetRenderDrawColorFloat(renderer, 0.1f, 0.5f, 1.0f, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderDebugTextFormat(renderer, 0.f, 0.f, "Optimal Moves: %u", this->optimal_moves);
    SDL_RenderDebugTextFormat(renderer, 0.f, 10.f, "Moves: %d", this->move_counter);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

scene* game_menu_scene::switch_scene()
{
    // for now only simple scene switch, same as all other scene, when scenes has branching it will differ
    if(this->switch_scene_flag){
        this->switch_scene_flag=false;
        return this->next_scene;
    }else{
        return this;
    }
}

void game_menu_scene::set_next_scene(scene* const next_scene)
{
    this->next_scene = next_scene;
}

void game_menu_scene::reset()
{
    this->optimal_moves = this->tower.get_optimal();
    this->tower.reset_start();
    this->move_counter = 0;
    this->move_index = 0;
}

void game_menu_scene::resize(const int new_window_width, const int new_window_height)
{
    this->tower_gui.resize(new_window_width, new_window_height);
}

bool game_menu_scene::has_move() const
{
    return this->move_index != 0;
}

int game_menu_scene::get_move() const
{
    return this->move_positions[0];
}

bool game_menu_scene::get_show_target() const {
    return this->show_target;
}