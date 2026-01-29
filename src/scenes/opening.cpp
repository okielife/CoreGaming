#include "../game.h"
#include "opening.h"

void Opening::update(Game& game, float const dt)
{
    this->overallSceneTime += dt;
    if (this->overallSceneTime < this->endTimeFadingInWizard)
    {
        this->phase = ScenePhase::FadingInWizard;
        if (this->timerFadingInWizard < 0.0) this->timerFadingInWizard = 0.0;
        this->timerFadingInWizard += dt;
    }
    else if (this->overallSceneTime < this->endTimeSpell)
    {
        this->phase = ScenePhase::Spell;
        if (this->timeSpell < 0.0) this->timeSpell = 0.0;
        this->timeSpell += dt;
    }
    else if (this->overallSceneTime < this->endTimeFlash)
    {
        this->phase = ScenePhase::Flash;
        if (this->timeFlash < 0.0) this->timeFlash = 0.0;
        this->timeFlash += dt;
    }
    else if (this->overallSceneTime < this->endTimeTitle)
    {
        this->phase = ScenePhase::Title;
        if (this->timeTitle < 0.0) this->timeTitle = 0.0;
        this->timeTitle += dt;
    }
    else
    {
        this->done = true;
    }
}

void Opening::render(Game& game, Renderer& renderer)
{
    switch (this->phase)
    {
    case ScenePhase::FadingInWizard:
        {
            float const scaledTime = std::clamp(this->timerFadingInWizard / this->durationFadingInWizard, 0.f, 1.f);
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
            float const scaledTime = std::clamp(this->timeFlash / this->durationFlash, 0.f, 1.f);
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
