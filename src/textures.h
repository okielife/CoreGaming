#pragma once
#include <string>
#include <unordered_map>

struct SDL_Renderer;
struct SDL_Texture;
using TextureID = __uint32_t;

// I think we need to abandon this and just let the Renderer class hold all the textures
// and texture IDs

class TextureManager {
public:
    explicit TextureManager(SDL_Renderer* r);
    ~TextureManager();

    TextureID load(const std::string& path);
    SDL_Texture* get(TextureID id) const;

private:
    SDL_Renderer* renderer_;
    std::unordered_map<TextureID, SDL_Texture*> textures_;
    TextureID nextId_ = 1;
};
