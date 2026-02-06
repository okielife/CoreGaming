#pragma once

#include <array>
#include <map>

#include <scenes/base.h>

class Game;
class Renderer;

enum class MenuOption
{
    GridShow,
    WizardSpells,
    Platformer,
    BulletHell,
    Maze,
    Exit
};
const std::map<MenuOption, const char *> menuOptions = {
    {MenuOption::GridShow, "Grid Show"},
    {MenuOption::WizardSpells, "Flashy Wizard Spells"},
    {MenuOption::Platformer, "Platformer"},
    {MenuOption::BulletHell, "Bullet Hell"},
    {MenuOption::Maze, "Maze"},
    {MenuOption::Exit, "Exit"}
};
constexpr std::array optionOrder = {
    MenuOption::GridShow,
    MenuOption::WizardSpells,
    MenuOption::Platformer,
    MenuOption::BulletHell,
    MenuOption::Maze,
    MenuOption::Exit,
};

// TODO: Add render status enum like fade in, fade out, changing menu options, etc., for a polished and animated look

struct SceneTitle : SceneBase
{
    explicit SceneTitle(const Game & game);
    ~SceneTitle() override = default;
    void reset(Game & game) final;
    void reenter(Game & game) final;
    void update(Game & game, float) final;
    void render(Game & game, Renderer & renderer) final;
    MenuOption currentOption = MenuOption::GridShow;
};
