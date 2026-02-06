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

/**
 * The enumerated font IDs, should be one per available font in the assets
 */
enum class FontID
{
    None,
    JollyLodger,
    UbuntuRegular
};

struct Text
{
    std::string text;
    sf::Color color;
    FontID fontID;
    int fontSize;
};

// TODO: I think each drawable needs its own transform, unless I can make all of them support all transformations

struct Rect {
    float w;
    float h;
    sf::Color color;
    sf::Color outlineColor;
    float outlineThickness;
};

/**
 * The enumerated sprite IDs, should be one per available sprite in the assets
 */
enum class SpriteID
{
    None,
    Wizard,
    Sky
};

struct Sprite {
    SpriteID id;
    sf::IntRect texRect;
};
