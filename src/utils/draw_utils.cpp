#include "draw_utils.hpp"

void draw_outie_rectangle_weighted(SDL_Renderer* renderer, SDL_FRect* rect, 
    const float red, const float green, const float blue, const float alpha, const float weight)
{
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, alpha);
    // top rectangle
    SDL_FRect border_rect{rect->x - weight, rect->y - weight, rect->w + 2*weight, weight};
    SDL_RenderFillRect(renderer, &border_rect);
    //bottom rectangle
    border_rect.y = rect->y + rect->h;
    SDL_RenderFillRect(renderer, &border_rect);
    //left rectangle
    border_rect.y = rect->y;
    border_rect.w = weight;
    border_rect.h = rect->h;
    SDL_RenderFillRect(renderer, &border_rect);
    //right rectangle
    border_rect.x = rect->x + rect->w;
    SDL_RenderFillRect(renderer, &border_rect);
}

void draw_outie_rectangle_weighted(SDL_Renderer* renderer, SDL_FRect* rect, 
    const float_color& color, const float weight)
{
    draw_outie_rectangle_weighted(renderer, rect, 
    color.red, color.green, color.blue, color.alpha, weight);
}


void draw_innie_rectangle_weighted(SDL_Renderer* renderer, SDL_FRect* rect, 
    const float red, const float green, const float blue, const float alpha, const float weight)
{
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, alpha);
    // top rectangle
    SDL_FRect border_rect{rect->x, rect->y, rect->w, weight};
    SDL_RenderFillRect(renderer, &border_rect);
    //bottom rectangle
    border_rect.y = rect->y + rect->h - weight;
    SDL_RenderFillRect(renderer, &border_rect);
    //left rectangle
    border_rect.y = rect->y + weight;
    border_rect.w = weight;
    border_rect.h = rect->h - 2*weight;
    SDL_RenderFillRect(renderer, &border_rect);
    //right rectangle
    border_rect.x = rect->x + rect->w - weight;
    SDL_RenderFillRect(renderer, &border_rect);
}

void draw_innie_rectangle_weighted(SDL_Renderer* renderer, SDL_FRect* rect, 
    const float_color& color, const float weight)
{
    draw_innie_rectangle_weighted(renderer, rect, 
    color.red, color.green, color.blue, color.alpha, weight);
}
