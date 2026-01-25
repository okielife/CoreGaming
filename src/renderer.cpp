#include "assets.h"
#include "renderer.h"

Renderer::Renderer(sf::RenderWindow& window) : window(window)
{
    for (auto const & [id, filename] : FontMap)
    {
        if (id == FontID::None) continue;
        sf::Font font;
        font.loadFromFile(AssetManager::font(filename).c_str());
        this->fonts.insert({id, font});
    }
    for (auto const & [id, filename] : TextureMap)
    {
        if (id == TextureID::None) continue;
        sf::Texture texture;
        texture.loadFromFile(AssetManager::texture(filename).c_str());
        this->textures.insert({id, texture});
    }
}

void Renderer::begin() const
{
    this->window.clear(sf::Color::Black);
}

void Renderer::end() const
{
    this->window.display();
}

sf::Rect<float> Renderer::worldRectangleToScreenRectangle(float const x, float const y, float const w, float const h, const Camera& cam) {
    return {(x - cam.x) * cam.zoom, (y - cam.y) * cam.zoom, w * cam.zoom, h * cam.zoom};
}

void Renderer::drawWorldRectangleOutline(const float x, const float y, const float w, const float h, const Camera& cam, const sf::Color & color) const
{
    auto const rect = worldRectangleToScreenRectangle(x, y, w, h, cam);
    this->drawScreenRectangleOutline(rect.left, rect.top, rect.width, rect.height, color);
}

void Renderer::drawScreenRectangleOutline(const float x, const float y, const float w, const float h, const sf::Color& color) const
{
    sf::RectangleShape rect;
    rect.setPosition(x, y);
    rect.setSize({w, h});
    rect.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    window.draw(rect);
}

void Renderer::drawScreenText(float x, float y, const char* text, const sf::Color color, FontID const fontID, int const fontSize) const
{
    auto& font = this->fonts.at(fontID);
    sf::Text drawable;
    drawable.setFont(font);
    drawable.setString(sf::String(text));
    drawable.setCharacterSize(fontSize);
    drawable.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    drawable.setPosition(x, y);
    window.draw(drawable);
}

void Renderer::drawScreenTexture(TextureID const tex, float const x, float const y, float const w, float const h) const
{
    auto& texture = textures.at(tex);
    sf::Sprite sprite(texture);
    sprite.setPosition(x, y);
    sprite.setScale(w / static_cast<float>(texture.getSize().x), h / static_cast<float>(texture.getSize().y));
    window.draw(sprite);
}
