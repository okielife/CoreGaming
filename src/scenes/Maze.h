#pragma once

#include <array>

#include <scenes/base.h>

constexpr int TILE_SIZE = 32;

struct SceneMaze : SceneBase
{
    void update(Game & game, float dt) final;
    void render(Game & game, Renderer & renderer) final;
    Rect player {.w = TILE_SIZE, .h = TILE_SIZE, .color = sf::Color::White};
    Rect wall {.w = TILE_SIZE, .h = TILE_SIZE, .color = {60, 60, 60, 255}};
    Rect path {.w = TILE_SIZE, .h = TILE_SIZE, .color = {180, 180, 180, 255}};
    Rect final {.w = TILE_SIZE, .h = TILE_SIZE, .color = sf::Color::Red};
    int playerXIndex = 1; // make sure these are on the valid path in the map
    int playerYIndex = 2;
    Transform playerTransform;
    Transform mapTileTransform;
    static constexpr std::array<std::string_view, 15> map = {
        "XXXXXXXXXXXXXXXXX",
        "XXXXXXXXXXXXXXXXX",
        "X011111111111XXXX",
        "XXXXXXXXXXXX1XXXX",
        "X111XX1111111XXXX",
        "X1X1XX1XXXXXXXXXX",
        "X1X1XX1111XXX1112",
        "X1X1XXXXX1XXX1XXX",
        "X1X1XXXXX1XXX1XXX",
        "X1X1111111XXX1XXX",
        "X1XXXXXXXXXXX1XXX",
        "X1XXXXXXXXXXX1XXX",
        "X11111111111X1XXX",
        "XXXXXXXXXXX111XXX",
        "XXXXXXXXXXXXXXXXX",
    };
    bool winner = false;
};
