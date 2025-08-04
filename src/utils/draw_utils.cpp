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


void draw_innie_rectangle_weighted(SDL_Renderer* renderer, const SDL_FRect* rect, 
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

void draw_innie_rectangle_weighted(SDL_Renderer* renderer, const SDL_FRect* rect, 
    const float_color& color, const float weight)
{
    draw_innie_rectangle_weighted(renderer, rect, 
    color.red, color.green, color.blue, color.alpha, weight);
}

void draw_bordered_rectangle_weighted(SDL_Renderer* renderer, const SDL_FRect& rect,
    const float red, const float green, const float blue, const float alpha, 
    const float red_border, const float green_border, const float blue_border, 
    const float alpha_border, const float weight)
{
    // border
    SDL_FRect border_rect = rect;
    // draw border
    draw_innie_rectangle_weighted(renderer, &border_rect, red_border, green_border, blue_border, alpha_border, weight);
    // body
    SDL_FRect& inside_rect = border_rect;
    inside_rect.x += weight;
    inside_rect.y += weight;
    inside_rect.w -= weight*2;
    inside_rect.h -= weight*2;
    // draw body
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, alpha);
    SDL_RenderFillRect(renderer, &inside_rect);
}


void draw_bordered_rectangle_weighted(SDL_Renderer* renderer, const SDL_FRect& rect,
    const float_color& body_color, const float_color& border_color, const float weight)
{
    draw_bordered_rectangle_weighted(renderer, rect, 
    body_color.red, body_color.green, body_color.blue, body_color.alpha,
    border_color.red, border_color.green, border_color.blue, border_color.alpha, weight);
}
