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
        this->fonts.insert({id, font});
    }
    for (auto const & [id, filename] : TextureMap)
    {
        if (id == TextureID::None) continue;
        sf::Texture texture;
        texture.loadFromFile(AssetManager::texture(filename).string());
        this->textures.insert({id, texture});
    }
    for (auto const & [id, filename] : SpriteMap)
    {
        if (id == SpriteID::None) continue;
        sf::Texture texture;
        texture.loadFromFile(AssetManager::sprite(filename).string());
        this->sprites.insert({id, texture});
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

void Renderer::drawSprite(const Sprite& s, const Transform& t) const
{
    auto& texture = sprites.at(s.id);
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

//
// void Renderer::drawWorldSprite(SpriteDraw const & s, Camera const & camera) const
// {
//     auto const rect = worldRectangleToScreenRectangle(s.position.x, s.position.y, s.rect.width, s.rect.height, camera);
//     auto const newSpriteDraw = SpriteDraw(s.sprite, rect.width, rect.height, rect.left, rect.top, s.scale.x, s.scale.y, s.rotation);
//     this->drawSprite(newSpriteDraw);
// }
//
// void Renderer::drawSprite(SpriteDraw const& s) const
// {
//     auto& texture = sprites.at(s.sprite);
//     sf::Sprite sprite;
//     sprite.setTexture(texture);
//     // TODO: Use this if it's a spritesheet
//     // if (s.rect.width > 0 && s.rect.height > 0) {
//     //     sprite.setTextureRect(s.rect);
//     // }
//     sprite.setPosition(s.position);
//     sprite.setScale(s.scale);
//     sprite.setRotation(s.rotation);
//     sprite.setColor(s.color);
//     window.draw(sprite);
// }
//
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
//
// void Renderer::drawScreenSFRectangle(sf::RectangleShape const & rect) const
// {
//     window.draw(rect);
// }