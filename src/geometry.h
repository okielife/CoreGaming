#pragma once

#include <SFML/Graphics/Color.hpp>

struct Transform {
    float x = 0;
    float y = 0;
    float rotation = 0;
    float sx = 1;
    float sy = 1;
    sf::Color color = sf::Color::White;
};

struct Rect {
    float w;
    float h;
    sf::Color color;
    sf::Color outlineColor;
    float outlineThickness;
};

struct AABB {
    float x;
    float y;
    float w;
    float h;
};

inline bool intersects(const AABB& a, const AABB& b)
{
    return !(a.x + a.w < b.x ||
             b.x + b.w < a.x ||
             a.y + a.h < b.y ||
             b.y + b.h < a.y);
}
inline AABB makeAABB(const Transform& t, const Rect& r)
{
    return { t.x, t.y, r.w, r.h };
}
