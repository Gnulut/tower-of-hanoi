#define SDL_MAIN_USE_CALLBACKS 1 
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <vector>

#include "tower_data.hpp"
#include "draw_utils.hpp"
#include "engine.hpp"
#include "config.hpp"
#include "main_menu.hpp"
#include "game_menu.hpp"
#include "scene.hpp"

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]){
    SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, std::to_string(constants::FPS).c_str());
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    // init systems
    engine* game_engine = new engine;
    main_menu_scene* main_menu = new main_menu_scene(game_engine->get_tower());
    game_menu_scene* game_menu = new game_menu_scene(game_engine->get_tower());
    game_engine->set_first_scene(main_menu);
    main_menu->set_next_scene(game_menu);
    game_menu->set_next_scene(main_menu);
    
    *appstate = game_engine;
    if (!SDL_CreateWindowAndRenderer("Tower of Hanoi", constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, 0, &game_engine->window, &game_engine->renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if(!SDL_SetRenderDrawBlendMode(game_engine->renderer, SDL_BLENDMODE_BLEND)){
        SDL_Log("Couldn't set render draw blend mode: %s", SDL_GetError());
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event){
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return ((engine*) appstate)->event(event);
}

SDL_AppResult SDL_AppIterate(void* appstate){
    engine* game_engine = (engine*)appstate;
    game_engine->render();
    game_engine->try_switch();
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result){
    /* SDL will clean up the window/renderer for us. */
}
