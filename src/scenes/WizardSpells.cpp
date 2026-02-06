#include <iostream>

#include <game.h>
#include <scenes/WizardSpells.h>

void SceneWizardSpells::update(Game& game, float const dt)
{
    if (game.input.wasPressed(Action::Quit))
    {
        this->done = true;
        this->nextScene = SceneID::Title;
        return;
    }

    this->overallSceneTime += dt;
    for (auto & [phaseID, animation] : this->animationSteps)
    {
        if (this->overallSceneTime < animation.endTime)
        {
            this->phase = phaseID;
            if (animation.stepTimer < 0.0) animation.stepTimer = 0.0;
            animation.stepTimer += dt;
            return;
        }
    }
    this->nextScene = SceneID::Title;
    this->done = true;  // fall through means we are done with animation steps
}

void SceneWizardSpells::render(Game& game, Renderer& renderer)
{
    renderer.begin(defaultCamera);
    const auto animation = this->animationSteps.at(this->phase);
    switch (this->phase)
    {
    case ScenePhase::FadingInWizard:
        {
            float const scaledTime = std::clamp(animation.stepTimer / animation.duration, 0.f, 1.f);
            this->wizardTransform.color = sf::Color(255, 255, 255,static_cast<int>(255 * scaledTime));
            renderer.draw(this->wizard, this->wizardTransform);
        }
        break;
    case ScenePhase::Spell:
        {
            renderer.drawScreenText(100, 200, "*Spell*", sf::Color::Green);
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
            renderer.drawScreenText(150, 150, "Flashy Wizard Spells", sf::Color::White, FontID::JollyLodger, 88);
        }
        break;
    }
    renderer.end();
}
