#include "title.h"
#include "../game.h"
#include "../constants.h"

SceneTitle::SceneTitle(const Game&)
{
}

void SceneTitle::reset(Game&)
{
}

void SceneTitle::reenter(Game&)
{
}

void SceneTitle::update(Game& game, const float)
{
    // if (game.input.anyPressed())
    // {
    //     this->done = true;
    // }
    if (game.input.wasPressed(Action::MoveDown))
    {
        switch (this->currentOption)
        {
        case MenuOption::GridShow: this->currentOption = MenuOption::WizardSpells; break;
        case MenuOption::WizardSpells: this->currentOption = MenuOption::Platformer; break;
        case MenuOption::Platformer: this->currentOption = MenuOption::BulletHell; break;
        case MenuOption::BulletHell: this->currentOption = MenuOption::Maze; break;
        case MenuOption::Maze: this->currentOption = MenuOption::Exit; break;
        case MenuOption::Exit: this->currentOption = MenuOption::GridShow; break;
        }
    }
    if (game.input.wasPressed(Action::MoveUp))
    {
        switch (this->currentOption)
        {
        case MenuOption::GridShow: this->currentOption = MenuOption::Exit; break;
        case MenuOption::WizardSpells: this->currentOption = MenuOption::GridShow; break;
        case MenuOption::Platformer: this->currentOption = MenuOption::WizardSpells; break;
        case MenuOption::BulletHell: this->currentOption = MenuOption::Platformer; break;
        case MenuOption::Maze: this->currentOption = MenuOption::BulletHell; break;
        case MenuOption::Exit: this->currentOption = MenuOption::Maze; break;
        }
    }
    if (game.input.wasPressed(Action::Confirm))
    {
        switch (this->currentOption)
        {
        case MenuOption::GridShow: this->nextScene = SceneID::GridShow; break;
        case MenuOption::WizardSpells: this->nextScene = SceneID::WizardSpells; break;
        case MenuOption::Platformer: this->nextScene = SceneID::Platformer; break;
        case MenuOption::BulletHell: this->nextScene = SceneID::BulletHell; break;
        case MenuOption::Maze: this->nextScene = SceneID::Maze; break;
        case MenuOption::Exit: this->nextScene = SceneID::Exit; break;
        }
        this->done = true;
    }
    if (game.input.wasPressed(Action::Quit))
    {
        this->nextScene = SceneID::Title;
        this->done = true;
    }
}

void SceneTitle::render(Game&, Renderer& renderer)
{
    if (this->done) return;

    renderer.drawScreenTexture(
        TextureID::Sky,
        0, 0,
        WINDOW_WIDTH, WINDOW_HEIGHT
    );

    renderer.drawScreenText(
        150.f,
        80.f,
        "This is a great menu screen!",
        sf::Color::Red,
        FontID::JollyLodger,
        60
    );

    renderer.drawScreenText(
        30.f,
        140.f,
        "Use up/down to select an option and press enter to continue",
        sf::Color::Red,
        FontID::JollyLodger,
        40
    );

    float yValue = 200.0;
    for (auto const& option : optionOrder)
    {
        yValue += 50;
        bool const selected = option == this->currentOption;
        renderer.drawScreenText(
            200.0f, yValue,
            menuOptions.at(option),
            selected ? sf::Color::Green : sf::Color::White,
            FontID::JollyLodger,
            selected ? 40 : 36
        );
        if (selected)
        {
            renderer.drawScreenRectangleOutline(180, yValue + 20, 10, 10, sf::Color::Green);
        }
    }
}
