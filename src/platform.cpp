#include <filesystem>

#include <platform.h>
#include <renderer.h>

Platform::Platform() : renderer(window), window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close) {
    // set ONE of these two options, not both
    this->window.setVerticalSyncEnabled(true);
    //this->window.setFramerateLimit(60);
    // Get the desktop resolution
    sf::VideoMode const desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int const desktopWidth = desktopMode.width;
    unsigned int const desktopHeight = desktopMode.height;

    // Calculate the window position for centering
    // The top-left corner of the window should be positioned at:
    int const windowPosX = (desktopWidth / 2) - (WINDOW_WIDTH / 2);
    int const windowPosY = (desktopHeight / 2) - (WINDOW_HEIGHT / 2);

    // Create the window
    window.setPosition(sf::Vector2i(windowPosX, windowPosY));
}

void Platform::run(Game & game) {

    //game.init(); as needed to load things like textures

    while (window.isOpen())
    {
        input_.beginFrame();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                input_.update(event);
                break;

            default:
                break;
            }
        }
        if (!game.running)
        {
            window.close();
        }

        float const dt = clock.restart().asSeconds();
        game.update(dt);
        this->audio_.update();

        game.render(renderer);

    }
}
