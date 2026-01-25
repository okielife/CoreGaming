#include "textures.h"

#include <SDL2/SDL_image.h>
#include <SDL_log.h>

TextureManager::TextureManager(SDL_Renderer* r)
: renderer_(r)
{
}

TextureManager::~TextureManager() {
    for (auto& [id, tex] : textures_) {
        SDL_DestroyTexture(tex);
    }
}

TextureID TextureManager::load(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        SDL_Log("IMG_Load failed: %s", IMG_GetError());
        return 0;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        SDL_Log("CreateTexture failed: %s", SDL_GetError());
        return 0;
    }

    TextureID id = nextId_++;
    textures_[id] = texture;
    return id;
}

SDL_Texture* TextureManager::get(TextureID id) const {
    auto it = textures_.find(id);
    return it != textures_.end() ? it->second : nullptr;
}
