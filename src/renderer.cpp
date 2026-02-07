#include <assets.hpp>
#include <renderer.hpp>

void Renderer::begin(const Camera& cam)
{
    worldView.setCenter(cam.x, cam.y);
    worldView.setSize(static_cast<float>(cam.w), static_cast<float>(cam.h));
    window.setView(worldView);
    window.clear(sf::Color::Black);
}

void Renderer::end() const
{
    window.display();
}

void Renderer::draw(const Text& t, const Transform& tr) const
{
    setWorldView();
    drawText(t, tr);
}
void Renderer::draw(const Sprite& s, const Transform& t) const
{
    setWorldView();
    drawSprite(s, t);
}
void Renderer::draw(const Rect& r, const Transform& t) const
{
    setWorldView();
    drawRectangle(r, t);
}
void Renderer::drawUI(const Text& t, const Transform& tr) const
{
    setUIView();
    drawText(t, tr);
}
void Renderer::drawUI(const Sprite& s, const Transform& t) const
{
    setUIView();
    drawSprite(s, t);
}
void Renderer::drawUI(const Rect& r, const Transform& t) const
{
    setUIView();
    drawRectangle(r, t);
}

void Renderer::setWorldView() const
{
    window.setView(worldView);
}

void Renderer::setUIView() const
{
    window.setView(screenView);
}

void Renderer::drawText(const Text& t, const Transform& tr) const
{
    sf::Font const font = AssetManager::font(t.font);
    sf::Text text;
    text.setFont(font);
    text.setString(sf::String(t.text));
    text.setCharacterSize(t.fontSize);
    auto const alpha = static_cast<sf::Uint8>(static_cast<float>(t.color.a) * tr.visibility);
    text.setFillColor(sf::Color(t.color.r, t.color.g, t.color.b, alpha));
    text.setPosition(tr.x, tr.y);
    text.setRotation(tr.rotation);
    text.setScale(tr.sx, tr.sy);
    window.draw(text);
}

void Renderer::drawSprite(const Sprite& s, const Transform& t) const
{
    sf::Texture texture = AssetManager::texture(s.texture);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(s.texRect);
    sprite.setPosition(t.x, t.y);
    sprite.setRotation(t.rotation);
    sprite.setScale(t.sx, t.sy);
    sprite.setColor({255, 255, 255, static_cast<sf::Uint8>(255 * t.visibility)});
    window.draw(sprite);
}

void Renderer::drawRectangle(const Rect& r, const Transform& t) const
{
    sf::RectangleShape shape;
    shape.setSize({r.w, r.h});
    shape.setFillColor(r.color);
    shape.setOutlineColor(r.outlineColor);
    shape.setOutlineThickness(r.outlineThickness);
    shape.setPosition(t.x, t.y);
    shape.setRotation(t.rotation);
    shape.setScale(t.sx, t.sy);
    window.draw(shape);
}

void Renderer::fullScreenOverlay(sf::Color const color) const
{
    sf::RectangleShape rect;
    rect.setSize({
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)
    });
    rect.setPosition(0.f, 0.f);
    rect.setFillColor(color);
    window.draw(rect);
}
