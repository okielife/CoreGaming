#pragma once

#include <array>

#include <scenes/base.hpp>
#include <drawables.hpp>

constexpr int TILE_WIDTH = WINDOW_WIDTH / 17;
constexpr int TILE_HEIGHT = WINDOW_HEIGHT / 15;

struct SceneMaze : SceneBase
{
    void update(Game & game, float dt) final;
    void render(Game & game, Renderer & renderer) final;
    Rect player {.w = TILE_WIDTH, .h = TILE_HEIGHT, .color = sf::Color::White};
    Rect wall {.w = TILE_WIDTH, .h = TILE_HEIGHT, .color = {60, 60, 60, 255}};
    Rect path {.w = TILE_WIDTH, .h = TILE_HEIGHT, .color = {180, 180, 180, 255}};
    Rect final {.w = TILE_WIDTH, .h = TILE_HEIGHT, .color = sf::Color::Red};
    int playerXIndex = 1; // make sure these are on the valid path in the map
    int playerYIndex = 2;
    Transform playerTransform;
    Transform mapTileTransform;
    Text message {.text = "", .color = sf::Color::Blue};
    Transform messageTransform {.x = 20, .y = 20};
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
