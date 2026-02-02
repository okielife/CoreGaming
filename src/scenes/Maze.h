#pragma once

#include <array>
#include "base.h"

class Game;
class Renderer;

constexpr int TILE_SIZE = 32;
constexpr int MAP_WIDTH = 17;
constexpr int MAP_HEIGHT = 15;

struct SceneMaze : SceneBase
{
    SceneMaze();
    ~SceneMaze() override = default;
    void reset(Game & game) final;
    void reenter(Game & game) final;
    void update(Game & game, float dt) final;
    void render(Game & game, Renderer & renderer) final;
    sf::Vector2i playerPos{0, 0};
    float speed_{200};  // think of it like game units per second
    const std::array<std::string, 15> map = {
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
    bool isBlocked(int const x, int const y) const
    {
        return this->map[y][x] == 'X';
    }
};
