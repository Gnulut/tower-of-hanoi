#pragma once

#include <SDL3/SDL.h>

#include "color.hpp"

// Draws a rectangle with an "outie" effect (beveled outward appearance) with a given weight.
//
// Parameters:
// - renderer: The SDL renderer to draw with.
// - rect: Pointer to the rectangle to draw (position and size).
// - red, green, blue, alpha: Color values (0–255).
// - weight: Thickness of the border, or how strong the outie effect should appear.
void draw_outie_rectangle_weighted(SDL_Renderer* renderer, SDL_FRect* rect, 
    const float red, const float green, const float blue, const float alpha, const float weight);

void draw_outie_rectangle_weighted(SDL_Renderer* renderer, SDL_FRect* rect, 
    const float_color& color, const float weight);

void draw_innie_rectangle_weighted(SDL_Renderer* renderer, SDL_FRect* rect, 
    const float red, const float green, const float blue, const float alpha, const float weight);

void draw_innie_rectangle_weighted(SDL_Renderer* renderer, SDL_FRect* rect, 
    const float_color& color, const float weight);