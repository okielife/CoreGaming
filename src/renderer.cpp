#include <SDL2/SDL_ttf.h>

#include "assets.h"
#include "renderer.h"

Renderer::Renderer(SDL_Renderer* r) : r_(r)
{
    TTF_Init();
    auto font_path = AssetManager::font("Ubuntu-Regular.ttf");
    this->font = TTF_OpenFont(font_path.string().c_str(), 24);
    this->textColor = {255, 255, 255, 0};
}

void Renderer::begin() {
    TTF_Init();
    SDL_SetRenderDrawColor(r_, 20, 20, 20, 255);
    SDL_RenderClear(r_);
}

void Renderer::end() {}

void Renderer::drawRect(const float x, const float y, const float w, const float h, const Camera& cam, const SDL_Color color) {
    const SDL_FRect rect{
        x - cam.x,
        y - cam.y,
        w,
        h
    };
    SDL_SetRenderDrawColor(r_, color.r, color.g, color.b, color.a);
    SDL_RenderFillRectF(r_, &rect);
}

void Renderer::drawText(float x, float y, const char* text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        SDL_Log("TTF_RenderText failed: %s", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(r_, surface);
    if (!texture) {
        SDL_Log("CreateTexture failed: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect rect;
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_FreeSurface(surface);

    SDL_RenderCopy(r_, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}