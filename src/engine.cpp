#include "engine.hpp"

engine::engine()
{
    // setting up
    main_menu_scene* main_menu = new main_menu_scene(tower);
    game_menu_scene* game_menu = new game_menu_scene(tower);
    this->set_first_scene(main_menu);
    main_menu->set_next_scene(game_menu);
    game_menu->set_next_scene(main_menu);

    // remember to delete
    this->add_scene(main_menu);
    this->add_scene(game_menu);
}

engine::~engine()
{
    while(!this->scenes.empty()){
        delete this->scenes.back();
        this->scenes.pop_back();
    }
}

void engine::render() const
{
    // default background
    SDL_SetRenderDrawColorFloat(this->renderer, 0.3f, 0.3f, 0.3f, SDL_ALPHA_OPAQUE_FLOAT);// background color
    SDL_RenderClear(this->renderer);
    // scene render
    this->current_scene->render(this->renderer);
    // present
    SDL_RenderPresent(this->renderer);
}

SDL_AppResult engine::event(SDL_Event* event)
{
    // engine events
    switch(event->type){
        case SDL_EVENT_QUIT: {
            return SDL_APP_SUCCESS;
        }
        case SDL_EVENT_WINDOW_RESIZED:{
            this->resize();
            return SDL_APP_CONTINUE;
        }
        default:{
            return this->current_scene->event(event);
        }
    }
}

void engine::resize()
{
    int new_window_width, new_window_height;
    SDL_GetWindowSize(this->window, &new_window_width, &new_window_height);
    SDL_Log(" engine: %d %d",new_window_height, new_window_width);
    for(auto&scene:this->scenes){
        scene->resize(new_window_width, new_window_height);
    }
}

void engine::try_switch()
{
    scene* next_scene = this->current_scene->switch_scene();
    current_scene = next_scene;
}

tower_data& engine::get_tower()
{
    return this->tower;
}

void engine::set_first_scene(scene* first_scene)
{
    this->current_scene=first_scene;
}

void engine::add_scene(scene* new_scene)
{
    this->scenes.push_back(new_scene);
}

SDL_Window*& engine::get_window()
{
    return this->window;
}

SDL_Renderer*& engine::get_renderer()
{
    return this->renderer;
}