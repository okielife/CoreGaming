#pragma once
#include "camera.h"

struct Color {
    unsigned char r, g, b, a;
};

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void begin() = 0;
    virtual void end() = 0;
    virtual void drawRect(float x, float y, float w, float h, const Camera& cam, Color color) = 0;
};
