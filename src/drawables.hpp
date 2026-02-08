#pragma once

#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

struct Transform {
    float x = 0;
    float y = 0;
    float rotation = 0;
    float sx = 1;
    float sy = 1;
    float visibility = 1.0;
};

struct Text
{
    std::string text;
    sf::Color color;
    std::string_view font = "ubuntu.ttf";
    int fontSize = 24;
};

struct Rect {
    float w = 0.0;
    float h = 0.0;
    sf::Color color;
    sf::Color outlineColor;
    float outlineThickness = 0.0;
};

struct Sprite {
    std::string texture;
    sf::IntRect texRect;
};
