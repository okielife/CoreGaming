#pragma once

#include <map>

#include <constants.hpp>
#include <drawables.hpp>
#include <rooms/RoomBase.hpp>

enum class ScenePhase
{
    FadingInWizard,
    Spell,
    Flash,
    Title,
    SubTitle
};

// eventually I would imagine this has its own update and render class
// in addition to the needed flexibility, it would be easier to test as well
struct AnimationStep
{
    float startTime = -1.0;
    float duration = -1.0;
    float endTime = -1.0;
    mutable float stepTimer = -1.0f;
    AnimationStep(float const startTime, float const duration)
    {
        this->startTime = startTime;
        this->duration = duration;
        this->endTime = startTime + duration;
    }
};

class RoomWizardSpells : public RoomBase {
public:
    void update(Game & game, float dt) override;
    void render(Game & game, Renderer &renderer) override;
private:
    float overallSceneTime = 0.f;
    Sprite wizard {.texture = "wizard.png", .texRect = {0, 0, 193, 241}};
    Transform wizardTransform = {.x = 10, .y = 10, .rotation = 0.0f, .sx = 2, .sy = 2};
    Text spell {.text = "*SPELL*", .color = sf::Color::Green};
    Transform spellTransform {.x = 100, .y = 200};
    Text title {.text = "Flashy Wizard Spells", .color = sf::Color::White, .font = "jolly.ttf", .fontSize = 88};
    Transform titleTransform {.x = 150, .y = 150};
    Text anyKey {.text = "Press any key to continue", .color = sf::Color::White, .font = AssetNaming::FontJolly, .fontSize = 40};
    Transform anyKeyTransform {.x = 240, .y = 350};

    ScenePhase phase = ScenePhase::FadingInWizard;
    const std::map<ScenePhase, AnimationStep> animationSteps = {
        {ScenePhase::FadingInWizard, AnimationStep(0.0f, 2.0)},
        {ScenePhase::Spell, AnimationStep(2.0, 0.25)},
        {ScenePhase::Flash, AnimationStep(2.25, 0.25)},
        {ScenePhase::Title, AnimationStep(2.5, 2.0)},
        {ScenePhase::SubTitle, AnimationStep(3.5, 1000.0)},
    };
};
