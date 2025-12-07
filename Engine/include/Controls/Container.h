//
// Created by XL1TTE on 29.11.2025.
//

#ifndef XLENGINE_CONTAINER_H
#define XLENGINE_CONTAINER_H
#include "Behaviour/GameObject.h"
namespace sf
{
class RectangleShape;
}

namespace xl
{
class Container final : public GameObject
{
  public:
    explicit Container(const std::weak_ptr<sf::RectangleShape> &);

  protected:
    std::weak_ptr<sf::RectangleShape> m_container;
    bool                              m_shouldFillWidth = false;

  protected:
    void Draw(const std::weak_ptr<sf::RenderTarget> &) override;
    void FillEmptyWidth() const;

  public:
    sf::Transform      GetTransform() const override;
    sf::Vector2<float> GetSize() const override;
    sf::Vector2<float> GetPosition() const override;
    Container         &FullWidth();
};

#endif // XLENGINE_CONTAINER_H
}