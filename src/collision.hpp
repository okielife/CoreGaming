#pragma once

#include <drawables.hpp>

/**
 * @file collision.hpp
 *
 * This file contains structs and workers related to collision.
 * The main idea is likely to be very thin lightweight structs
 * that can be created from a variety of shapes and then common
 * collision routines.
 *
 * @ingroup collision
 */

/**
 * @brief A rectangular AABB (axis aligned bounding box) struct
 *
 * It's basically a rectangle with position, in an attempt to be
 * as calculation efficient as possible.
 */
struct AABB {
    float x;
    float y;
    float w;
    float h;
};

/**
 * @brief Checks intersection between two rectangular AABB instances.
 *
 * @param a The first AABB instance
 * @param b The second AABB instance
 * @return true if they intersect, or false if not
 */
inline bool intersects(const AABB& a, const AABB& b)
{
    return !(a.x + a.w < b.x ||
             b.x + b.w < a.x ||
             a.y + a.h < b.y ||
             b.y + b.h < a.y);
}

/**
 * @brief Creates a lightweight AABB instance from drawable rectangle objects
 *
 * @param t A drawable transformation object, used to define the position of the object
 * @param r A drawable rectangle object, used to define the size of the object
 * @return An instantiated lightweight AABB object
 */
inline AABB makeAABB(const Transform& t, const Rect& r)
{
    return { t.x, t.y, r.w, r.h };
}
