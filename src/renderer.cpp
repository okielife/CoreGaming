#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "assets.h"
#include "renderer.h"

#include <ranges>

Renderer::Renderer(SDL_Renderer* r) : r_(r)
{
    for (auto const & [id, font] : FontMap)
    {
        if (id == FontID::None) continue;
        auto [filename, size] = font;
        auto fontInstance = TTF_OpenFont(AssetManager::font(filename).c_str(), size);
        this->fonts.insert({id, fontInstance});
    }
}

Renderer::~Renderer()
{
    for (const auto& tex : textures_ | std::views::values) {
        SDL_DestroyTexture(tex);
    }
    for (const auto& font : this->fonts | std::views::values)
    {
        TTF_CloseFont(font);
    }
}

void Renderer::begin() const
{
    SDL_SetRenderDrawColor(r_, 20, 20, 20, 255);
    SDL_RenderClear(r_);
}

void Renderer::end() {}

SDL_FRect Renderer::worldRectangleToScreenRectangle(float const x, float const y, float const w, float const h, const Camera& cam) {
    return {(x - cam.x) * cam.zoom, (y - cam.y) * cam.zoom, w * cam.zoom, h * cam.zoom};
}

void Renderer::drawWorldRectangleOutline(const float x, const float y, const float w, const float h, const Camera& cam, const SDL_Color color) const
{
    SDL_FRect const rect = worldRectangleToScreenRectangle(x, y, w, h, cam);
    SDL_SetRenderDrawColor(r_, color.r, color.g, color.b, color.a);
    SDL_RenderFillRectF(r_, &rect);
}

void Renderer::drawScreenText(float x, float y, const char* text, const SDL_Color color, FontID const fontID) const
{
    auto fontInstance = this->fonts.at(fontID);
    SDL_Surface* surface = TTF_RenderText_Solid(fontInstance, text, color);
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

    SDL_Rect const rect{static_cast<int>(x), static_cast<int>(y), surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(r_, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

void Renderer::drawScreenTexture(
    TextureID const tex,
    float const x, float const y,
    float const w, float const h
) const
{
    SDL_Texture* texture = textures_.find(tex)->second;
    const SDL_FRect dst { x, y, w, h };
    SDL_RenderCopyF(r_, texture, nullptr, &dst);
}

TextureID Renderer::loadTexture(const std::filesystem::path& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        SDL_Log("IMG_Load failed: %s", IMG_GetError());
        return 0;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(r_, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        SDL_Log("CreateTexture failed: %s", SDL_GetError());
        return 0;
    }

    const TextureID id = nextId_++;
    textures_[id] = texture;
    return id;
}

// void Renderer::drawSprite(
//     TextureID texture,
//     const SDL_Rect& src,
//     float x,
//     float y,
//     const Camera& cam
// ) {
//     SDL_FRect dst {
//         (x - cam.x) * cam.zoom,
//         (y - cam.y) * cam.zoom,
//         src.w * cam.zoom,
//         src.h * cam.zoom
//     };
//
//     SDL_RenderCopy(
//         r_,
//         textureManager_.get(texture),
//         &src,
//         &dst
//     );
// }