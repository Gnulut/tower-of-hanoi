#include "engine.hpp"

#include <iostream>
engine::engine(){};

void engine::render() {
    // default background
    SDL_SetRenderDrawColor(this->renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);// background color
    SDL_RenderClear(this->renderer);
    // scene render
    this->current_scene->render(this->renderer);
    // present
    SDL_RenderPresent(this->renderer);
}

SDL_AppResult engine::event(SDL_Event* event){
    // engine events
    if(event->type == SDL_EVENT_QUIT){
        return SDL_APP_SUCCESS;
    }
    // scene events
    return this->current_scene->event(event);
}

void engine::try_switch(){
    scene* next_scene = this->current_scene->switch_scene();
    current_scene = next_scene;
}

tower_data& engine::get_tower(){
    return this->tower;
}

void engine::set_first_scene(scene* first_scene){
    this->current_scene=first_scene;
}