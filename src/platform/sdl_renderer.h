#pragma once
#include <SDL.h>
#include "../engine/renderer.h"

class SDLRenderer : public Renderer {
public:
    explicit SDLRenderer(SDL_Renderer* r);

    void begin() override;
    void end() override;

    void drawRect(
        float x, float y, float w, float h,
        const Camera& cam, Color color
    ) override;

private:
    SDL_Renderer* r_;
};
