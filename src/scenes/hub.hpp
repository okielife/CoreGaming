#pragma once

#include <array>
#include <map>

#include <scenes/base.hpp>
#include <renderer.hpp> // TODO: Why do I have to have this here but not other level headers?
#include <command.hpp>

const std::map<GameCommand, const char *> menuOptions = {
    {GameCommand::GridShow, "Grid Show"},
    {GameCommand::WizardSpells, "Flashy Wizard Spells"},
    {GameCommand::Platformer, "Platformer"},
    {GameCommand::BulletHell, "Bullet Hell"},
    {GameCommand::Maze, "Maze"},
    {GameCommand::Exit, "Exit"}
};
constexpr std::array optionOrder = {
    GameCommand::GridShow,
    GameCommand::WizardSpells,
    GameCommand::Platformer,
    GameCommand::BulletHell,
    GameCommand::Maze,
    GameCommand::Exit,
};

// TODO: Add render status enum like fade in, fade out, changing menu options, etc., for a polished and animated look

struct HubState : GameState
{
    ~HubState() override = default;
    void update(Game & game, float) final;
    void render(Game & game, Renderer & renderer) final;
    GameCommand currentOption = GameCommand::GridShow;
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
};
