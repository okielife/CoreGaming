#include "../game.h"
#include "Maze.h"

class Game;

SceneMaze::SceneMaze()
{
    // Find start position
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            if (map[y][x] == '0') {
                playerPos = {x, y};
            }
        }
    }
}

void SceneMaze::reset(Game &) {}

void SceneMaze::reenter(Game &) {}

void SceneMaze::update(Game & game, const float dt)
{
    const auto& input = game.input;
    if (input.wasPressed(Action::Quit))
    {
        this->done = true;
        this->nextScene = SceneID::Exit;
    }
    sf::Vector2i nextPos = this->playerPos;
    if (input.wasPressed(Action::MoveUp)) nextPos.y--;
    if (input.wasPressed(Action::MoveDown))  nextPos.y++;
    if (input.wasPressed(Action::MoveLeft))  nextPos.x--;
    if (input.wasPressed(Action::MoveRight)) nextPos.x++;
    if (!this->isBlocked(nextPos.x, nextPos.y)) {
        this->playerPos = nextPos;
    }
    if (map[playerPos.y][playerPos.x] == '2')
    {
        winner = true;
    }
}

void SceneMaze::render(Game &, Renderer & renderer)
{
    // Draw map
    sf::Color tileColor;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            if (char const c = map[y][x]; c == 'X')
                tileColor = sf::Color(60, 60, 60);
            else if (c == '1')
                tileColor = sf::Color(180, 180, 180);
            else if (c == '0')
                tileColor = sf::Color(180, 180, 180); // sf::Color::Green;
            else if (c == '2')
                tileColor = sf::Color::Red;
            renderer.drawScreenRectangleOutline(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, tileColor);;
        }
    }
    // Draw player
    renderer.drawSprite(SpriteDraw(SpriteID::Wizard, TILE_SIZE, TILE_SIZE, playerPos.x * TILE_SIZE, playerPos.y * TILE_SIZE, 0.15, 0.12, 0, sf::Color::White));
    if (winner)
    {
        renderer.drawScreenText(20, 50, "WINNER!", sf::Color::Green);
    } else
    {
        renderer.drawScreenText(20, 50, "Use WASD", sf::Color::Red);
        std::string const coordsString = "Player X, Y = " + std::to_string(this->playerPos.x) + ", " + std::to_string(this->playerPos.y);
        renderer.drawScreenText(200, 70, coordsString.c_str(), sf::Color::Red);
    }
}