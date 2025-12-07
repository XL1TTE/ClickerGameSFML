//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_GAMETEXT_H
#define CLICKER_GAMETEXT_H
#include "Behaviour/GameObject.h"

namespace sf
{
class Text;
class Font;
class RenderTarget;
class Color;
} // namespace sf

class GameText : public xl::GameObject
{
  public:
    explicit GameText(const sf::Font &);

  protected:
    std::unique_ptr<sf::Text> m_textView;

  protected:
    void Draw(const std::weak_ptr<sf::RenderTarget> &) override;

  public:
    GameText          &SetText(const std::string &text);
    GameText          &SetColor(const sf::Color color);
    GameText          &SetFontSize(const unsigned int size);
    GameText          &AlignCenter();
    sf::Vector2<float> getSize() override;
    sf::Vector2<float> getPosition() override;
    sf::Transform      getTransform() override;

    void Destroy() override;
};

#endif // CLICKER_GAMETEXT_H
