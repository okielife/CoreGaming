#pragma once

/**
 * @brief Camera defining the visible world region.
 *
 * The Camera maps world coordinates into screen space.
 * It is intentionally backend-agnostic and contains no SDL types.
 *
 * @ingroup EngineCore
 */
struct Camera {
    float x = 0.0;
    float y = 0.0;
    int w = 0.0;
    int h = 0.0;
};
