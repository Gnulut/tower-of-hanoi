#include "main_menu.hpp"

main_menu_scene::main_menu_scene(tower_data& tower):
    tower(tower), tower_height_button(tower)
{
    // tower height button
    this->buttons[this->tower_height_button_index] = &this->tower_height_button;
    // tower position button (start)
    this->buttons[this->tower_start_position_index] = &this->tower_start_position_button;
    // tower position button (target)
    this->buttons[this->tower_target_position_index] = &this->tower_target_position_button;
    this->tower_start_position_button.set_neighbour(&this->tower_target_position_button);
    this->tower_target_position_button.set_neighbour(&this->tower_start_position_button);
    // tower start game button
    this->tower_start_button.link_menu(this);
    this->buttons[this->tower_start_button_index] = &this->tower_start_button;

    // default selected button
    this->current_button_selected = 0;
    this->buttons[this->current_button_selected]->select();
}

main_menu_scene::~main_menu_scene()
{

}

SDL_AppResult main_menu_scene::event(SDL_Event *event)
{
    switch(event->type) {
        case SDL_EVENT_KEY_DOWN: {// keyboard
            SDL_Scancode key_scancode = event->key.scancode;
            switch (key_scancode) {
                case SDL_SCANCODE_W:
                    [[falltrough]]
                case SDL_SCANCODE_UP: {
                    // change into previous button
                    this->change_selected_button((this->current_button_selected + (this->button_count-1)) % this->button_count);
                    break;
                }
                case SDL_SCANCODE_S:
                    [[falltrough]]
                case SDL_SCANCODE_DOWN: {
                    // change into next button
                    this->change_selected_button((this->current_button_selected + 1) % this->button_count);
                    break;
                }
                default: {
                    this->buttons[this->current_button_selected]->event(event);
                    break;
                }
            }
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            SDL_FPoint mouse_point{event->button.x, event->button.y};
            if((int)event->button.button == SDL_BUTTON_LEFT) { // left click
                for(int button_index = 0; button_index < this->button_count; ++button_index) { // iterate button(s)
                    if(this->buttons[button_index]->inside(mouse_point)) { // hit any button
                        // button selected
                        this->buttons[this->current_button_selected]->unselect();
                        this->current_button_selected = button_index;
                        this->buttons[this->current_button_selected]->select();

                        // start button (special case [double click])
                        if(this->current_button_selected == this->tower_start_button_index && event->button.clicks >= 2){
                            this->change_scene();
                        }
                        break;
                    }
                }
            }
        }
        default: {
            // intentionally empty, represents unconfigured event
            break;
        }
    }
    return SDL_APP_CONTINUE;
}

void main_menu_scene::render(SDL_Renderer* renderer, SDL_Window* window) const
{
    for(int button_index=0; button_index < this->button_count; ++button_index){ // iterate button(s)
        this->buttons[button_index]->render(renderer);
    }
}

scene* main_menu_scene::switch_scene()
{
    // for now only simple scene switch, same as all other scene, when scenes has more complex branching it will differ
    if(this->switch_scene_flag){
        this->switch_scene_flag=false;
        this->next_scene->reset();
        return this->next_scene;
    }else{
        return this;
    }
}

void main_menu_scene::set_next_scene(scene* const next_scene)
{
    this->next_scene = next_scene;
}

void main_menu_scene::reset()
{
    
}

void main_menu_scene::resize(const int new_window_width, const int new_window_height)
{
    SDL_FRect rect = {0.1f*new_window_width, 0.1f*new_window_height,
                      0.3f*new_window_width, 0.3f*new_window_height};
    // tower height button
    this->tower_height_button.set_rect(rect);
    rect.x += 0.5f*new_window_width;

    // tower position button (start)
    this->tower_start_position_button.set_rect(rect);
    rect.y += 0.5f*new_window_height;

    // tower position button (target)
    this->tower_target_position_button.set_rect(rect);
    rect.x -= 0.5f*new_window_width;

    // tower start game button
    this->tower_start_button.set_rect(rect);
}

void main_menu_scene::change_scene()
{
    tower.new_game(std::get<int>(this->buttons[0]->get_value()), 
        std::get<start_or_target_position>(buttons[1]->get_value()),
        std::get<start_or_target_position>(buttons[2]->get_value()));
    this->switch_scene_flag=true;
}

void main_menu_scene::change_selected_button(int button_number)
{
    this->buttons[this->current_button_selected]->unselect();
    this->current_button_selected = button_number;
    this->buttons[this->current_button_selected]->select();
}