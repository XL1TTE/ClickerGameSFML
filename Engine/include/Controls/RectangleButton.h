//
// Created by XL1TTE on 07.12.2025.
//

#ifndef XLENGINE_BUTTON_H
#define XLENGINE_BUTTON_H

#include "Behaviour/GameObject.h"
#include "LayoutObject.h"

namespace sf
{
class RectangleShape;
}
namespace sf
{
class Shape;
} // namespace sf

namespace sf
{
class Text;
class Font;
class RenderTarget;
class Color;
} // namespace sf
namespace xl
{
class TextMesh;

class RectangleButton : public LayoutObject<sf::RectangleShape>
{
  public:
    explicit RectangleButton(const sf::RectangleShape &mesh);
    ~RectangleButton() override;

    void SetLabel(const std::string &&label, const sf::Font &font);

    void ChangeText(const std::string &text) const;
    void SetColor(const sf::Color &color) const;

    [[nodiscard]] sf::Vector2<float> GetPosition() const override;
    [[nodiscard]] sf::Vector2<float> GetSize() const override;
    void                             Draw(const std::weak_ptr<sf::RenderTarget> &) override;

  protected:
    std::unique_ptr<TextMesh> m_label;
};
} // namespace xl
#endif // XLENGINE_BUTTON_H
