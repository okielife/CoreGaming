#include "sdl_renderer.h"

SDLRenderer::SDLRenderer(SDL_Renderer* r) : r_(r) {}

void SDLRenderer::begin() {
    SDL_SetRenderDrawColor(r_, 20, 20, 20, 255);
    SDL_RenderClear(r_);
}

void SDLRenderer::end() {}

void SDLRenderer::drawRect(
    const float x, const float y, const float w, const float h,
    const Camera& cam, const Color color
) {
    const SDL_FRect rect{
        x - cam.x,
        y - cam.y,
        w,
        h
    };

    SDL_SetRenderDrawColor(r_, color.r, color.g, color.b, color.a);
    SDL_RenderFillRectF(r_, &rect);
}
