#pragma once


enum class GameCommand {
    None,
    PushPause,
    PopPause,
    Exit,
    // StartBattle
    // StartCutScene
};

enum class RoomID
{
    None,

    Hub,
    GridShow,
    WizardSpells,
    Platformer,
    BulletHell,
    Maze,

    // Others
};

enum class WorldEvent
{
    None,
    Exit
};
