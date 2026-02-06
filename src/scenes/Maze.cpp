#include <game.h>
#include <scenes/Maze.h>

class Game;

void SceneMaze::update(Game & game, const float dt)
{
    const auto& input = game.input;
    if (input.wasPressed(Action::Quit))
    {
        this->done = true;
        this->nextScene = SceneID::Title;
    }
    int nextX = playerXIndex;
    int nextY = playerYIndex;
    if (input.wasPressed(Action::MoveUp)) nextY--;
    if (input.wasPressed(Action::MoveDown))  nextY++;
    if (input.wasPressed(Action::MoveLeft))  nextX--;
    if (input.wasPressed(Action::MoveRight)) nextX++;
    // assuming that the path is bounded by valid wall tiles here
    if (this->map[nextY][nextX] != 'X') {
        this->playerXIndex = nextX;
        this->playerYIndex = nextY;
    }
    if (map[playerYIndex][playerXIndex] == '2')
    {
        winner = true;
    }
    playerTransform.x = playerXIndex * TILE_SIZE;
    playerTransform.y = playerYIndex * TILE_SIZE;
}

void SceneMaze::render(Game &, Renderer & renderer)
{
    renderer.begin(fixedDefaultCamera);
    // Draw map
    for (int y = 0; y < this->map.size(); ++y) {
        for (int x = 0; x < this->map[0].size(); ++x) {
            mapTileTransform.x = x * TILE_SIZE;
            mapTileTransform.y = y * TILE_SIZE;
            if (char const c = map[y][x]; c == 'X')
                renderer.draw(wall, mapTileTransform);
            else if (c == '1' || c == '0')
                renderer.draw(path, mapTileTransform);
            else if (c == '2')
                renderer.draw(final, mapTileTransform);
        }
    }
    // Draw player
    renderer.draw(player, playerTransform);

    if (winner)
    {
        renderer.drawScreenText(20, 50, "WINNER!", sf::Color::Green);
    } else
    {
        renderer.drawScreenText(20, 50, "Use Arrow Keys", sf::Color::Red);
        std::string const coordsString = "Player X, Y = " + std::to_string(this->playerXIndex) + ", " + std::to_string(this->playerYIndex);
        renderer.drawScreenText(200, 70, coordsString.c_str(), sf::Color::Red);
    }
    renderer.end();
}