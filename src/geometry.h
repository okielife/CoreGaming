#pragma once

#include <drawables.h>

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
