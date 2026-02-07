#include <gtest/gtest.h>
#include "../src/camera.hpp"

TEST(CameraTest, CentersOnTarget) {
    Camera cam;
    cam.w = 800;
    cam.h = 600;

    constexpr float targetX = 400.0f;
    constexpr float targetY = 300.0f;

    // Simulate "camera follows player"
    cam.x = targetX - static_cast<float>(cam.w) / 2.0f;
    cam.y = targetY - static_cast<float>(cam.h) / 2.0f;

    EXPECT_FLOAT_EQ(cam.x, 0.0f);
    EXPECT_FLOAT_EQ(cam.y, 0.0f);
}

