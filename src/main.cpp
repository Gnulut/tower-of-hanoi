#define SDL_MAIN_USE_CALLBACKS 1 
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "engine.hpp"

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]){
    SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, std::to_string(constants::FPS).c_str());
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    // init system(s)
    engine* game_engine = new engine;
    
    *appstate = game_engine;
    if (!SDL_CreateWindowAndRenderer("Tower of Hanoi", 
        constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, 0, 
        &game_engine->get_window(), &game_engine->get_renderer())) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if(!SDL_SetRenderDrawBlendMode(game_engine->get_renderer(), SDL_BLENDMODE_BLEND)){
        SDL_Log("Couldn't set render draw blend mode: %s", SDL_GetError());
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event){
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
    delete (engine*) appstate;
}
