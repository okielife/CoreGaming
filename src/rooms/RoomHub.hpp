#pragma once

#include <array>
#include <map>

#include <rooms/RoomBase.hpp>
#include <renderer.hpp>
#include <command.hpp>

class World;

const std::map<RoomID, const char *> menuOptions = {
    {RoomID::GridShow, "Grid Show"},
    {RoomID::WizardSpells, "Flashy Wizard Spells"},
    {RoomID::Platformer, "Platformer"},
    {RoomID::BulletHell, "Bullet Hell"},
    {RoomID::Maze, "Maze"},
};
constexpr std::array optionOrder = {
    RoomID::GridShow,
    RoomID::WizardSpells,
    RoomID::Platformer,
    RoomID::BulletHell,
    RoomID::Maze,
};

// TODO: Add render status enum like fade in, fade out, changing menu options, etc., for a polished and animated look

struct RoomHub : RoomBase
{
    explicit RoomHub(World& world) : world(world) {}
    ~RoomHub() override = default;
    void update(Game & game, float) final;
    void render(Game & game, Renderer & renderer) final;
    RoomID currentOption = RoomID::GridShow;
    Sprite sky { .texture = "sky.png", .texRect = {0, 0, 800, 600}};
    Transform skyTransform;
    Rect selectedRect {.w = 10, .h = 10, .outlineColor = sf::Color::Green, .outlineThickness = 1.f};
    Transform selectedTransform {.x = 180};
    Text title {.text = "This is a great menu screen!", .color = sf::Color::Red, .font = "jolly.ttf", .fontSize = 60};
    Transform titleTransform {.x = 150, .y = 80};
    Text subTitle {.text = "Use up/down to select an option and press enter to continue", .color = sf::Color::Red, .font = "jolly.ttf", .fontSize = 40};
    Transform subTitleTransform {.x = 30, .y = 140};
    Text optionText {.text = "", .font = "jolly.ttf"};
    Transform optionTextTransform {.x = 200};
    Rect crossedOutOption {.w = 120, .h = 4, .color = sf::Color::Red, .outlineColor = sf::Color::Black, .outlineThickness = 1.f};
    Transform crossedOutTransform {.x = 195, .rotation = -2.8};
    World& world;
private:
    std::unique_ptr<RoomBase> currentRoom;
    bool exitIsSelected = false;
};
