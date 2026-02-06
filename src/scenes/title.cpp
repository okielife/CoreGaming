#include <scenes/title.h>
#include <game.h>


void SceneTitle::update(Game& game, const float)
{
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
        this->nextScene = SceneID::Exit;
        this->done = true;
    }
}

void SceneTitle::render(Game&, Renderer& renderer)
{
    if (this->done) return;

    renderer.begin(fixedDefaultCamera);
    renderer.draw(this->sky, this->skyTransform);

    renderer.drawUI(title, titleTransform);
    renderer.drawUI(subTitle, subTitleTransform);

    float yValue = 200.0;
    for (auto const& option : optionOrder)
    {
        yValue += 50;
        bool const selected = option == this->currentOption;
        optionText.text = menuOptions.at(option);
        optionText.color = selected ? sf::Color::Green : sf::Color::White;
        optionText.fontSize = selected ? 40 : 36;
        optionTextTransform.y = yValue;
        renderer.drawUI(optionText, optionTextTransform);
        selectedTransform.y = yValue + 20;
        if (selected) renderer.draw(selectedRect, selectedTransform);
    }
    renderer.end();
}
