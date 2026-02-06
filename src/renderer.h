#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include <camera.h>
#include <geometry.h>

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
 * The enumerated font IDs, should be one per available font in the assets
 */
enum class FontID
{
    None,
    JollyLodger,
    UbuntuRegular24
};

/**
 * A mapping of the font ID to the filename in the assets/fonts directory.
 * Update this accordingly whenever fonts are added/changed/removed.
 */
inline const std::unordered_map<FontID, std::string> FontMap = {
    {FontID::JollyLodger, "JollyLodger-Regular.ttf"},
    {FontID::UbuntuRegular24, "Ubuntu-Regular.ttf"}
};

/**
 * The enumerated texture IDs, should be one per available texture in the assets
 */
enum class TextureID
{
    None,
    Sky
};

/**
 * A mapping of the texture ID to the filename in the assets/textures directory.
 * Update this accordingly whenever textures are added/changed/removed.
 */
inline const std::unordered_map<TextureID, std::string> TextureMap = {
    {TextureID::Sky, "sky.png"}
};

/**
 * The enumerated sprite IDs, should be one per available sprite in the assets
 */
enum class SpriteID
{
    None,
    Wizard
};

/**
 * A mapping of the sprite ID to the filename in the assets/sprites directory.
 * Update this accordingly whenever sprites are added/changed/removed.
 */
inline const std::unordered_map<SpriteID, std::string> SpriteMap = {
    {SpriteID::Wizard, "wizard.png"}
};

struct Sprite {
    SpriteID id;
    sf::IntRect texRect;
};

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

    /**
     * @brief Transforms a game-world rectangle position/size into a screen geometry rectangle.
     *
     * @param x The x-coordinate in the game world, in game-units
     * @param y The y-coordinate in the game world, in game-units
     * @param w The width in the game world, in game-units
     * @param h The height in the game world, in game-units
     * @param cam The camera instance which tells how to transform world geometry into screen geometry
     * @return A screen-coordinate (pixel) rectangle which can be displayed using the platform renderer
     */
    static sf::Rect<float> worldRectangleToScreenRectangle(float x, float y, float w, float h, const Camera& cam);

    /**
     * @brief Draws a game-world rectangle on the screen from world/game coordinates based on camera position and zoom
     *
     * @param x The x-coordinate in the game world, in game-units
     * @param y The y-coordinate in the game world, in game-units
     * @param w The width in the game world, in game-units
     * @param h The height in the game world, in game-units
     * @param cam The camera instance which tells how to transform world geometry into screen geometry
     * @param color The outline color of the rectangle
     */
    void drawWorldRectangleOutline(float x, float y, float w, float h, const Camera& cam, const sf::Color & color) const;

    /**
     * @brief Draws a rectangle on the screen given screen coordinates (pixels), not world coordinates
     *
     * @param x The x-coordinate on the screen, in pixels
     * @param y The y-coordinate on the screen, in pixels
     * @param w The width on the screen, in pixels
     * @param h The height on the screen, in pixels
     * @param color The outline color of the rectangle
     */
    void drawScreenRectangleOutline(float x, float y, float w, float h, const sf::Color& color) const;

    /**
     * @brief Draws text on the screen given screen coordinates, not world coordinates
     *
     * @param x The x-coordinate on the screen, in pixels
     * @param y The y-coordinate on the screen, in pixels
     * @param text The text string to write on the screen
     * @param color The color of the text
     * @param fontID The FontID enumeration value to use for rendering the text
     * @param fontSize The font size for the text
     */
    void drawScreenText(float x, float y, const char * text, sf::Color color, FontID fontID = FontID::UbuntuRegular24, int fontSize = 24) const;

    /**
     * @brief Draws a given texture to the screen given screen coordinates
     *
     * @param tex The texture ID to draw, based on the loadTexture method return value
     * @param x The x-coordinate on the screen, in pixels
     * @param y The y-coordinate on the screen, in pixels
     * @param w The width of the texture to draw, in pixels
     * @param h The height of the texture to draw, in pixels
     */
    void drawScreenTexture(TextureID tex, float x, float y, float w, float h) const;

    void fullScreenOverlay(sf::Color color) const;
    void draw(const Sprite& s, const Transform& t) const;
    void draw(const Rect& r, const Transform& t) const;
    void drawUI(const Sprite& s, const Transform& t) const;
    void drawUI(const Rect& r, const Transform& t) const;
    //void addScreenShake(float time);
private:
    void setWorldView() const;
    void setUIView() const;
    void drawSprite(const Sprite& s, const Transform& t) const;
    void drawRectangle(const Rect& r, const Transform& t) const;

    sf::View worldView;
    sf::View screenView;
    sf::RenderWindow& window;
    std::unordered_map<TextureID, sf::Texture> textures;
    std::unordered_map<SpriteID, sf::Texture> sprites;
    std::unordered_map<FontID, sf::Font> fonts;
};
