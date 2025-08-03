#pragma once

#include <SDL3/SDL.h>

// base class for managing event and rendering
class scene{ 
public:
    virtual ~scene() = default;

    // handle events
    virtual SDL_AppResult event(SDL_Event* event) = 0;

    // render
    virtual void render(SDL_Renderer* renderer) = 0;

    // switching menus
    virtual scene* switch_scene() = 0;

    // refresh datas
    virtual void reset() = 0;

protected:
    // provides a way to link to another scene
    scene* next_scene = nullptr;

    // flag to indicate request switching to another scene
    bool switch_scene_flag = false; 
};