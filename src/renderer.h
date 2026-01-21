#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "camera.h"

class Renderer {
public:
    explicit Renderer(SDL_Renderer* r);

    void begin();
    void end();

    void drawRect(float x, float y, float w, float h, const Camera& cam, SDL_Color color);
    void drawText(float x, float y, const char * text, SDL_Color color);

    TTF_Font *font;
    SDL_Renderer* r_;
    SDL_Color textColor;
};
