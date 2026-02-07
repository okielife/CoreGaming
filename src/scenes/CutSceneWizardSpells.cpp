#include <iostream>

#include <game.hpp>
#include <scenes/CutSceneWizardSpells.hpp>

void RoomWizardSpells::update(Game& game, float const dt)
{
    if (game.input.wasPressed(Action::Quit))
    {
        nextRoomID = RoomID::Hub;
        // roomOutcome = RoomOutcome::LeaveWorld;
        return;
    }
    overallSceneTime += dt;
    for (auto & [phaseID, animation] : animationSteps)
    {
        if (overallSceneTime < animation.endTime)
        {
            phase = phaseID;
            if (animation.stepTimer < 0.0) animation.stepTimer = 0.0;
            animation.stepTimer += dt;
            return;
        }
    }
    nextRoomID = RoomID::Hub;
    // roomOutcome = RoomOutcome::LeaveWorld;
}

void RoomWizardSpells::render(Game& game, Renderer& renderer)
{
    renderer.begin(fixedDefaultCamera);
    const auto animation = animationSteps.at(phase);
    switch (phase)
    {
    case ScenePhase::FadingInWizard:
        {
            float const scaledTime = std::clamp(animation.stepTimer / animation.duration, 0.f, 1.f);
            wizardTransform.visibility = scaledTime;
            renderer.draw(wizard, wizardTransform);
        }
        break;
    case ScenePhase::Spell:
        {
            renderer.drawUI(spell, spellTransform);
        }
        break;
    case ScenePhase::Flash:
        {
            float const scaledTime = std::clamp(animation.stepTimer / animation.duration, 0.f, 1.f);
            float const symmetricScaledTime = 1.f - std::abs(2.f * scaledTime - 1.f);
            float const shapedIntensity = symmetricScaledTime * symmetricScaledTime;   // square curve
            sf::Color c = sf::Color::White;
            c.a = static_cast<uint8_t>(180 * shapedIntensity);
            renderer.fullScreenOverlay(c);
        }
        break;
    case ScenePhase::Title:
        {
            renderer.drawUI(title, titleTransform);
        }
        break;
    }
    renderer.end();
}
