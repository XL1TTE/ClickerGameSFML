//
// Created by XL1TTE on 07.12.2025.
//

#ifndef CLICKER_CLICKERBUTTON_H
#define CLICKER_CLICKERBUTTON_H

#include "Behaviour/GameObject.h"

namespace sf
{
class RectangleShape;
}
class GameText;
namespace sf
{
class Text;
class Font;
class RenderTarget;
class Color;
} // namespace sf

class RectangleButton : public xl::GameObject
{
  public:
    RectangleButton();
    ~RectangleButton() override;

    RectangleButton &AlignCenter();
    void             SetLabel(std::unique_ptr<GameText> &label);
    void             ChangeText(const std::string &text) const;

    sf::Vector2<float> getPosition() override;
    sf::Vector2<float> GetSize() override;
    void               Draw(const std::weak_ptr<sf::RenderTarget> &) override;

  protected:
    std::unique_ptr<GameText>           m_label;
    std::unique_ptr<sf::RectangleShape> m_button;
};
#endif // CLICKER_CLICKERBUTTON_H
