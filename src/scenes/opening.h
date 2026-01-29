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

class Opening : public SceneBase {
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
    // timing for fading in wizard
    constexpr static float startTimeFadingInWizard = 0.f;
    constexpr static float durationFadingInWizard = 2.0;
    constexpr static float endTimeFadingInWizard = startTimeFadingInWizard + durationFadingInWizard;
    float timerFadingInWizard = -1.0f;
    // timing for casting the spell
    constexpr static float durationSpell = 0.25;
    constexpr static float endTimeSpell = endTimeFadingInWizard + durationSpell;
    float timeSpell = -1.0f;
    // timing for flashing the screen
    constexpr static float durationFlash = 0.25;
    constexpr static float endTimeFlash = endTimeSpell + durationFlash;
    float timeFlash = -1.0f;
    // timing for showing the title
    constexpr static float durationTitle = 2.0;
    constexpr static float endTimeTitle = endTimeFlash + durationTitle;
    float timeTitle = -1.0f;
};
