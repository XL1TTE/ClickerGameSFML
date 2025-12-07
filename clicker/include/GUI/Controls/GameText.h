//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_GAMETEXT_H
#define CLICKER_GAMETEXT_H
#include "Behaviour/GameObject.h"
#include "EventSystems/Events/IPointerEnterHandler.h"
#include "EventSystems/Events/IPointerExitHandler.h"

namespace sf
{
class Text;
class Font;
class RenderTarget;
class Color;
} // namespace sf

class GameText final : public xl::GameObject, public xl::IPointerEnterHandler, public xl::IPointerExitHandler
{
  public:
    explicit GameText(const sf::Font &);

  protected:
    std::unique_ptr<sf::Text> m_textView;

  protected:
    void Draw(const std::weak_ptr<sf::RenderTarget> &) override;

  public:
    GameText          &SetText(const std::string &text);
    GameText          &SetColor(sf::Color color);
    GameText          &SetFontSize(unsigned int size);
    GameText          &AlignCenter();
    sf::Vector2<float> GetSize() override;
    bool               Contains(sf::Vector2<float> point) override;
    sf::Vector2<float> getPosition() override;
    sf::Transform      getTransform() override;

    void OnPointerEnter(PointerEnterEvent event) override;
    void OnPointerExit(PointerExitEvent event) override;

    void Destroy() override;
};

#endif // CLICKER_GAMETEXT_H
