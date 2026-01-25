#pragma once

#include "constants.h"

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
    float x = 0.0;
    float y = 0.0;
    int w = WINDOW_WIDTH;
    int h = WINDOW_HEIGHT;
    float zoom = 1.0f; // 1.0 = 100%
};
