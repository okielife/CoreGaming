#include <scenes/hub.hpp>
#include <game.hpp>


void HubState::update(Game& game, const float)
{
    if (game.input.wasPressed(Action::MoveDown))
    {
        switch (currentOption)
        {
        case GameCommand::GridShow: currentOption = GameCommand::WizardSpells; break;
        case GameCommand::WizardSpells: currentOption = GameCommand::Platformer; break;
        case GameCommand::Platformer: currentOption = GameCommand::BulletHell; break;
        case GameCommand::BulletHell: currentOption = GameCommand::Maze; break;
        case GameCommand::Maze: currentOption = GameCommand::Exit; break;
        case GameCommand::Exit: currentOption = GameCommand::GridShow; break;
        default: break;
        }
    }
    if (game.input.wasPressed(Action::MoveUp))
    {
        switch (currentOption)
        {
        case GameCommand::GridShow: currentOption = GameCommand::Exit; break;
        case GameCommand::WizardSpells: currentOption = GameCommand::GridShow; break;
        case GameCommand::Platformer: currentOption = GameCommand::WizardSpells; break;
        case GameCommand::BulletHell: currentOption = GameCommand::Platformer; break;
        case GameCommand::Maze: currentOption = GameCommand::BulletHell; break;
        case GameCommand::Exit: currentOption = GameCommand::Maze; break;
        default: break;
        }
    }
    if (game.input.wasPressed(Action::Confirm))
    {
        switch (currentOption)
        {
        case GameCommand::GridShow: pendingCommand = GameCommand::GridShow; break;
        case GameCommand::WizardSpells: pendingCommand = GameCommand::WizardSpells; break;
        case GameCommand::Platformer: pendingCommand = GameCommand::Platformer; break;
        case GameCommand::BulletHell: pendingCommand = GameCommand::BulletHell; break;
        case GameCommand::Maze: pendingCommand = GameCommand::Maze; break;
        case GameCommand::Exit: pendingCommand = GameCommand::Exit; break;
        default: break;
        }
    }
    if (game.input.wasPressed(Action::Quit))
    {
        pendingCommand = GameCommand::Exit;
    }
}

void HubState::render(Game&, Renderer& renderer)
{
    if (pendingCommand != GameCommand::None) return;

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
