#include <scenes/title.hpp>
#include <game.hpp>


void SceneTitle::update(Game& game, const float)
{
    if (game.input.wasPressed(Action::MoveDown))
    {
        switch (currentOption)
        {
        case MenuOption::GridShow: currentOption = MenuOption::WizardSpells; break;
        case MenuOption::WizardSpells: currentOption = MenuOption::Platformer; break;
        case MenuOption::Platformer: currentOption = MenuOption::BulletHell; break;
        case MenuOption::BulletHell: currentOption = MenuOption::Maze; break;
        case MenuOption::Maze: currentOption = MenuOption::Exit; break;
        case MenuOption::Exit: currentOption = MenuOption::GridShow; break;
        }
    }
    if (game.input.wasPressed(Action::MoveUp))
    {
        switch (currentOption)
        {
        case MenuOption::GridShow: currentOption = MenuOption::Exit; break;
        case MenuOption::WizardSpells: currentOption = MenuOption::GridShow; break;
        case MenuOption::Platformer: currentOption = MenuOption::WizardSpells; break;
        case MenuOption::BulletHell: currentOption = MenuOption::Platformer; break;
        case MenuOption::Maze: currentOption = MenuOption::BulletHell; break;
        case MenuOption::Exit: currentOption = MenuOption::Maze; break;
        }
    }
    if (game.input.wasPressed(Action::Confirm))
    {
        switch (currentOption)
        {
        case MenuOption::GridShow: nextScene = SceneID::GridShow; break;
        case MenuOption::WizardSpells: nextScene = SceneID::WizardSpells; break;
        case MenuOption::Platformer: nextScene = SceneID::Platformer; break;
        case MenuOption::BulletHell: nextScene = SceneID::BulletHell; break;
        case MenuOption::Maze: nextScene = SceneID::Maze; break;
        case MenuOption::Exit: nextScene = SceneID::Exit; break;
        }
        done = true;
    }
    if (game.input.wasPressed(Action::Quit))
    {
        nextScene = SceneID::Exit;
        done = true;
    }
}

void SceneTitle::render(Game&, Renderer& renderer)
{
    if (done) return;

    renderer.begin(fixedDefaultCamera);
    renderer.draw(sky, skyTransform);

    renderer.drawUI(title, titleTransform);
    renderer.drawUI(subTitle, subTitleTransform);

    float yValue = 200.0;
    for (auto const& option : optionOrder)
    {
        yValue += 50;
        bool const selected = option == currentOption;
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
