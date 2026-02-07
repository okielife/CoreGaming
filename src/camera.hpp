#pragma once

#include <constants.hpp>

/**
 * @file camera.h
 * Classes and functions related to camera and transformation belong in this file
 *
 * @ingroup render
 */

/**
 * @brief A zoomable and movable camera defining the visible world region.
 *
 * The Camera maps world coordinates into screen space.
 * It is intentionally backend-agnostic and contains no SDL types.
 *
 * @ingroup render
 */
struct Camera {
    float x = WINDOW_WIDTH / 2.0f;
    float y = WINDOW_HEIGHT / 2.0f;
    int w = WINDOW_WIDTH;
    int h = WINDOW_HEIGHT;
    float zoom = 1.0f; // 1.0 = 100%
};

constexpr Camera fixedDefaultCamera {
    .x = WINDOW_WIDTH / 2.0f, .y = WINDOW_HEIGHT / 2.0f, .w = WINDOW_WIDTH, .h = WINDOW_HEIGHT, .zoom = 1.0f
};
