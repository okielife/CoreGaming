#pragma once

#include <SFML/Graphics.hpp>

#include <assets.hpp>
#include <camera.hpp>
#include <drawables.hpp>

/**
 * @file renderer.hpp
 * @brief Centralized rendering class, providing utilities for displaying on the screen
 *
 * The basic expectation for rendering goes like this:
 * - The Platform class holds the game event loop, and each frame asks the game to perform a frame
 * - The game class frame routine should do any updates, and then call the appropriate render method
 * - The render method has a reference to this Renderer class, and so it should call begin(), any draw*()
 *   methods, and then end()
 * - The Platform class will then flip the screen to show the new window to the user.
 *
 * @ingroup render
 */

/**
 * @brief Rendering management class for visual rendering on the screen
 *
 * This class is responsible for handling the "screen/window".
 * This class should provide convenient methods to display something on the screen, such as
 * shapes, text, textures, background images, using either world coordinates (the player's location), or
 * direct screen coordinates (the heads-up display or a health bar).
 * It is expected that this will be added to a lot initially as we figure out what
 * the game needs to render.
 *
 * @ingroup render
 */
class Renderer {
public:
    /**
     * @brief Primary constructor for the game engine renderer class
     *
     * @param window The platform (SFML) rendering instance
     */
    explicit Renderer(sf::RenderWindow& window): window(window) {};

    /**
     * @brief This function does any rendering initialization
     *
     * For now, the initialization for the renderer consists of just setting the draw color
     * and calling RenderClear to paint the background the draw color.  This must be called by
     * each scene at the beginning of their render step to clear the screen before immediately
     * drawing their assets.
     */
    void begin(const Camera& cam);

    /**
     * @brief This function wraps up any rendering once the drawn assets have been added
     *
     * As of now this function does not do anything, but we may need to add things later.
     * Game/scene render methods should call this at the end of their render function to
     * futureproof it in case this function does more later.
     */
    void end() const;

    void fullScreenOverlay(sf::Color color) const;
    void draw(const Text& t, const Transform& tr) const;
    void draw(const Sprite& s, const Transform& t) const;
    void draw(const Rect& r, const Transform& t) const;
    void drawUI(const Text& t, const Transform& tr) const;
    void drawUI(const Sprite& s, const Transform& t) const;
    void drawUI(const Rect& r, const Transform& t) const;
    //void addScreenShake(float time);

private:
    void setWorldView() const;
    void setUIView() const;
    void drawSprite(const Sprite& s, const Transform& t) const;
    void drawRectangle(const Rect& r, const Transform& t) const;
    void drawText(const Text& t, const Transform& tr) const;

    sf::View worldView;
    sf::View screenView = sf::View(
        sf::Vector2f(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0),
        sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)
        );
    sf::RenderWindow& window;
    AssetManager assets;
};
