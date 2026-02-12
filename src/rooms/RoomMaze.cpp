#include <game.hpp>
#include <movement.hpp>
#include <rooms/RoomMaze.hpp>

class Game;

void RoomMaze::update(Game & game, [[maybe_unused]] const float dt)
{
    const auto& input = game.input;
    if (input.pressedThisFrame(Action::Quit))
    {
        // TODO: Use a "won" flag instead so the screen stays on the maze.
        status = won ? RoomStatus::Complete : RoomStatus::Incomplete;
        return;
    }

    int const dx = input.axisCurrentDigitalValue(Axis::X);
    int const dy = input.axisCurrentDigitalValue(Axis::Y);
    int nextX = playerXIndex;
    int nextY = playerYIndex;
    if (horizontal.update(dt, dx))
    {
        nextX += dx;
    }

    if (vertical.update(dt, dy))
    {
        nextY += dy;
    }

    // assuming that the path is bounded by valid wall tiles here
    if (map[nextY][nextX] != 'X') {
        playerXIndex = nextX;
        playerYIndex = nextY;
    }
    if (map[playerYIndex][playerXIndex] == '2')
    {
        won = true;
    }
    playerTransform.x = static_cast<float>(playerXIndex) * TILE_WIDTH;
    playerTransform.y = static_cast<float>(playerYIndex) * TILE_HEIGHT;
}

void RoomMaze::render(Game &, Renderer & renderer)
{
    renderer.begin(fixedDefaultCamera);
    // Draw map
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[0].size(); ++x) {
            mapTileTransform.x = static_cast<float>(x) * TILE_WIDTH;
            mapTileTransform.y = static_cast<float>(y) * TILE_HEIGHT;
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

    if (won)
    {
        message.text = "WINNER!";
        message.color = sf::Color::Green;
        renderer.drawUI(message, messageTransform);
    } else
    {
        message.text = "Use Arrow Keys; Player X, Y = " + std::to_string(playerXIndex) + ", " + std::to_string(playerYIndex);
        message.color = sf::Color::Blue;
        renderer.drawUI(message, messageTransform);
    }
    renderer.end();
}