#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <sstream>
#include <iostream>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 600), "SFML Joystick Visualizer");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("/home/edwin/CLionProjects/CoreGaming/src/assets/fonts/ubuntu.ttf"))
        return -1;

    unsigned int joystickId = 0;

    if (!sf::Joystick::isConnected(joystickId))
    {
        std::cout << "No joystick connected to slot 0.\n";
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(30, 30, 30));

        if (sf::Joystick::isConnected(joystickId))
        {
            // --- HEADER INFO ---
            std::stringstream ss;
            ss << "Joystick " << joystickId
               << " | Buttons: " << sf::Joystick::getButtonCount(joystickId);
            sf::Text header(ss.str(), font, 22);
            header.setPosition(20, 20);
            header.setFillColor(sf::Color::White);
            window.draw(header);

            // --- AXES ---
            constexpr float startY = 100.f;
            float y = startY;
            for (int axis = 0; axis < sf::Joystick::AxisCount; ++axis)
            {
                if (sf::Joystick::hasAxis(joystickId, static_cast<sf::Joystick::Axis>(axis)))
                {
                    float value = sf::Joystick::getAxisPosition(
                        joystickId,
                        static_cast<sf::Joystick::Axis>(axis)
                    ); // -100 to 100

                    // Label

                    constexpr std::array axisNames = {"X", "Y", "Z", "R", "U", "V", "PovX", "PovY"};
                    sf::Text label(axisNames[axis], font, 18);
                    label.setPosition(20, y);
                    window.draw(label);

                    // Layout
                    constexpr float axisBarWidth = 400.f;
                    constexpr float axisBarHeight = 20.f;

                    // Background bar
                    sf::RectangleShape bg({axisBarWidth, axisBarHeight});
                    bg.setPosition(120, y);
                    bg.setFillColor(sf::Color(80, 80, 80));
                    window.draw(bg);

                    // Value bar (centered)
                    float normalized = value / 100.f;  // -1 to 1
                    float halfWidth = axisBarWidth / 2.f;

                    sf::RectangleShape fill({std::abs(normalized) * halfWidth, axisBarHeight});
                    fill.setPosition(
                        120 + halfWidth + (normalized < 0 ? normalized * halfWidth : 0),
                        y
                    );
                    fill.setFillColor(normalized >= 0 ? sf::Color::Green : sf::Color::Red);
                    window.draw(fill);

                    // Center line
                    sf::RectangleShape centerLine({2.f, axisBarHeight});
                    centerLine.setPosition(120 + halfWidth, y);
                    centerLine.setFillColor(sf::Color::White);
                    window.draw(centerLine);

                    y += 40.f;
                }
            }

            // --- BUTTONS ---
            unsigned int buttonCount = sf::Joystick::getButtonCount(joystickId);

            for (unsigned int i = 0; i < buttonCount; ++i)
            {
                bool pressed = sf::Joystick::isButtonPressed(joystickId, i);
                constexpr float buttonStartY = 100.f;
                constexpr float buttonStartX = 600.f;

                sf::RectangleShape button({40.f, 40.f});
                button.setPosition(
                    buttonStartX + static_cast<float>(i % 6) * 50.f,
                    buttonStartY + static_cast<float>(i) / 6 * 50.f
                );
                button.setFillColor(pressed ? sf::Color::Green : sf::Color(100, 100, 100));
                window.draw(button);

                sf::Text label(std::to_string(i), font, 16);
                label.setPosition(
                    button.getPosition().x + 12.f,
                    button.getPosition().y + 8.f
                );
                window.draw(label);
            }
        }
        else
        {
            sf::Text text("No joystick connected in slot 0",
                          font, 24);
            text.setPosition(200, 250);
            window.draw(text);
        }

        window.display();
    }

    return 0;
}
