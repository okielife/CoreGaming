#pragma once

#include "base.h"

class Game;
class Renderer;

enum class ScenePhase
{
    FadingInWizard,
    Spell,
    Flash,
    Title
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

class SceneWizardSpells : public SceneBase {
public:
    void reset(Game & game) override {};
    void reenter(Game & game) override {};
    void update(Game & game, float dt) override;
    void render(Game & game, Renderer &renderer) override;
private:
    Camera camera;
    float overallSceneTime = 0.f;
    SpriteDraw wizardSprite = SpriteDraw(SpriteID::Wizard, 0, 0, 200, 200);
    ScenePhase phase = ScenePhase::FadingInWizard;
    const std::map<ScenePhase, AnimationStep> animationSteps = {
        {ScenePhase::FadingInWizard, AnimationStep(0.0f, 2.0)},
        {ScenePhase::Spell, AnimationStep(2.0, 0.25)},
        {ScenePhase::Flash, AnimationStep(2.25, 0.25)},
        {ScenePhase::Title, AnimationStep(2.5, 2.0)},
    };
};
