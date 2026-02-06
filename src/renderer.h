#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include <camera.h>
#include <drawables.h>

/**
 * @file renderer.h
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
 * shapes, text, sprites, background images, using either world coordinates (the player's location), or
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
     * This class sets up internal connections to SFML stuff and initializes things
     * necessary for the client-facing API.  The constructor is responsible for:
     * - Initializing all fonts and textures that will be used in the game (inefficiently
     *   all at once for now, because it's easy)
     * @param window The platform (SFML) rendering instance
     */
    explicit Renderer(sf::RenderWindow& window);

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
    sf::View screenView;
    sf::RenderWindow& window;
    std::unordered_map<SpriteID, sf::Texture> spriteTextures;
    std::unordered_map<FontID, sf::Font> fontInstances;

    /**
     * A mapping of the sprite ID to the filename in the assets/sprites directory.
     * Update this accordingly whenever sprites are added/changed/removed.
     */
    const std::unordered_map<SpriteID, std::string> SpriteMap = {
        {SpriteID::Wizard, "wizard.png"},
        {SpriteID::Sky, "sky.png"}
    };
    /**
     * A mapping of the font ID to the filename in the assets/fonts directory.
     * Update this accordingly whenever fonts are added/changed/removed.
     */
    const std::unordered_map<FontID, std::string> FontMap = {
        {FontID::JollyLodger, "JollyLodger-Regular.ttf"},
        {FontID::UbuntuRegular, "Ubuntu-Regular.ttf"}
    };
};
