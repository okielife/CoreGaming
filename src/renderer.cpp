#include <assets.h>
#include <renderer.h>

Renderer::Renderer(sf::RenderWindow& window) : window(window)
{
    this->screenView.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->screenView.setCenter(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
    for (auto const & [id, filename] : FontMap)
    {
        if (id == FontID::None) continue;
        sf::Font font;
        font.loadFromFile(AssetManager::font(filename).string());
        this->fontInstances.insert({id, font});
    }
    for (auto const & [id, filename] : SpriteMap)
    {
        if (id == SpriteID::None) continue;
        sf::Texture texture;
        texture.loadFromFile(AssetManager::sprite(filename).string());
        this->spriteTextures.insert({id, texture});
    }
}

void Renderer::begin(const Camera& cam)
{
    this->worldView.setCenter(cam.x, cam.y);
    this->worldView.setSize(static_cast<float>(cam.w), static_cast<float>(cam.h));
    this->window.setView(this->worldView);
    this->window.clear(sf::Color::Black);
}

void Renderer::end() const
{
    this->window.display();
}

void Renderer::draw(const Text& t, const Transform& tr) const
{
    this->setWorldView();
    this->drawText(t, tr);
}
void Renderer::draw(const Sprite& s, const Transform& t) const
{
    this->setWorldView();
    this->drawSprite(s, t);
}
void Renderer::draw(const Rect& r, const Transform& t) const
{
    this->setWorldView();
    this->drawRectangle(r, t);
}
void Renderer::drawUI(const Text& t, const Transform& tr) const
{
    this->setUIView();
    this->drawText(t, tr);
}
void Renderer::drawUI(const Sprite& s, const Transform& t) const
{
    this->setUIView();
    this->drawSprite(s, t);
}
void Renderer::drawUI(const Rect& r, const Transform& t) const
{
    this->setUIView();
    this->drawRectangle(r, t);
}

void Renderer::setWorldView() const
{
    this->window.setView(this->worldView);
}

void Renderer::setUIView() const
{
    this->window.setView(this->screenView);
}

void Renderer::drawText(const Text& t, const Transform& tr) const
{
    auto& font = this->fontInstances.at(t.fontID);
    sf::Text text;
    text.setFont(font);
    text.setString(sf::String(t.text));
    text.setCharacterSize(t.fontSize);
    text.setFillColor(sf::Color(t.color.r, t.color.g, t.color.b, static_cast<sf::Uint8>(t.color.a * tr.visibility)));
    text.setPosition(tr.x, tr.y);
    text.setRotation(tr.rotation);
    text.setScale(tr.sx, tr.sy);
    window.draw(text);
}

void Renderer::drawSprite(const Sprite& s, const Transform& t) const
{
    auto& texture = spriteTextures.at(s.id);
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
