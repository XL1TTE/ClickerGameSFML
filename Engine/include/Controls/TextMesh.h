//
// Created by XL1TTE on 29.11.2025.
//

#ifndef XLENGINE_TEXT_MESH_H
#define XLENGINE_TEXT_MESH_H
#include "Behaviour/GameObject.h"
#include "LayoutObject.h"
#include "SFML/Graphics/Text.hpp"

namespace sf
{
class Font;
class RenderTarget;
class Color;
} // namespace sf

namespace xl
{
class TextMesh final : public LayoutObject<sf::Text>
{
  public:
    explicit TextMesh(const sf::Font &);
    ~TextMesh() override = default;

  public:
    void Draw(const std::weak_ptr<sf::RenderTarget> &) override;

  public:
    TextMesh                        &SetText(const std::string &text);
    TextMesh                        &SetColor(sf::Color color);
    TextMesh                        &SetFontSize(unsigned int size);
    TextMesh                        &AlignCenter();
    [[nodiscard]] sf::Vector2<float> GetSize() const override;
    [[nodiscard]] sf::Vector2<float> GetPosition() const override;
    [[nodiscard]] sf::Transform      GetTransform() const override;

    void OnDestroy() override;
};
} // namespace xl
#endif // XLENGINE_TEXT_MESH_H
