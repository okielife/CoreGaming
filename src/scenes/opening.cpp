#include "../game.h"
#include "opening.h"

#include <iostream>

void Opening::update(Game& game, float const dt)
{
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
    this->done = true;  // fall through means we are done with animation steps
}

void Opening::render(Game& game, Renderer& renderer)
{
    const auto animation = this->animationSteps.at(this->phase);
    switch (this->phase)
    {
    case ScenePhase::FadingInWizard:
        {
            float const scaledTime = std::clamp(animation.stepTimer / animation.duration, 0.f, 1.f);
            this->wizardSprite.color = sf::Color(255, 255, 255,static_cast<int>(255 * scaledTime));
            renderer.drawSprite(this->wizardSprite);
        }
        break;
    case ScenePhase::Spell:
        {
            renderer.drawScreenText(50, 20, "*Spell*", sf::Color::Green);
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
}
