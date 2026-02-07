#include <scenes/RoomHub.hpp>
#include <game.hpp>
#include <scenes/World.hpp>

void RoomHub::update(Game& game, const float)
{
    if (game.input.wasPressed(Action::MoveDown))
    {
        if (exitIsSelected)
        {
            currentOption = RoomID::GridShow;
            exitIsSelected = false;
        } else
        {
            switch (currentOption)
            {
            case RoomID::GridShow: currentOption = RoomID::WizardSpells; break;
            case RoomID::WizardSpells: currentOption = RoomID::Platformer; break;
            case RoomID::Platformer: currentOption = RoomID::BulletHell; break;
            case RoomID::BulletHell: currentOption = RoomID::Maze; break;
            case RoomID::Maze: currentOption = RoomID::None; exitIsSelected = true; break;
            default: break;
            }
        }
    }
    if (game.input.wasPressed(Action::MoveUp))
    {
        if (exitIsSelected)
        {
            currentOption = RoomID::Maze;
            exitIsSelected = false;
        } else
        {
            switch (currentOption)
            {
            case RoomID::GridShow: currentOption = RoomID::None; exitIsSelected = true; break;
            case RoomID::WizardSpells: currentOption = RoomID::GridShow; break;
            case RoomID::Platformer: currentOption = RoomID::WizardSpells; break;
            case RoomID::BulletHell: currentOption = RoomID::Platformer; break;
            case RoomID::Maze: currentOption = RoomID::BulletHell; break;
            default: break;
            }
        }
    }
    if (game.input.wasPressed(Action::Confirm))
    {
        if (exitIsSelected)
        {
            roomOutcome = RoomOutcome::LeaveWorld;
            return;
        }
        switch (currentOption)
        {
        case RoomID::GridShow: nextRoomID = RoomID::GridShow; break;
        case RoomID::WizardSpells: nextRoomID = RoomID::WizardSpells; break;
        case RoomID::Platformer: nextRoomID = RoomID::Platformer; break;
        case RoomID::BulletHell: nextRoomID = RoomID::BulletHell; break;
        case RoomID::Maze: nextRoomID = RoomID::Maze; break;
        default: break;
        }
    }
    if (game.input.wasPressed(Action::Quit))
    {
        roomOutcome = RoomOutcome::LeaveWorld;
    }
}

void RoomHub::render(Game&, Renderer& renderer)
{
    if (nextRoomID != RoomID::None) return;

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
        if (world.isRoomCompleted(option)) {
            crossedOutTransform.y = yValue + 25;
            renderer.drawUI(crossedOutOption, crossedOutTransform);
        }
        selectedTransform.y = yValue + 20;
        if (selected) renderer.draw(selectedRect, selectedTransform);
    }

    // exit is no longer a room option, but a game command
    yValue += 50;
    optionText.text = "Exit";
    optionText.color = exitIsSelected ? sf::Color::Green : sf::Color::White;
    optionText.fontSize = exitIsSelected ? 40 : 36;
    optionTextTransform.y = yValue;
    renderer.drawUI(optionText, optionTextTransform);
    selectedTransform.y = yValue + 20;
    if (exitIsSelected) renderer.draw(selectedRect, selectedTransform);

    renderer.end();
}
