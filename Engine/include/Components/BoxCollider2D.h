//
// Created by XL1TTE on 07.12.2025.
//

#ifndef XLENGINE_BOXCOLLIDER2D_H
#define XLENGINE_BOXCOLLIDER2D_H

#include "SFML/Graphics/RectangleShape.hpp"

namespace xl
{
struct BoxCollider2D
{
  public:
    explicit BoxCollider2D(sf::Vector2f size);
    ~BoxCollider2D() = default;

  private:
    sf::RectangleShape m_collider;

  public:
    sf::Vector2f GetSize() const;
    bool         Contains(sf::Vector2f point) const;
};

inline BoxCollider2D::BoxCollider2D(const sf::Vector2f size)
    : m_collider(size)
{
}
inline sf::Vector2f BoxCollider2D::GetSize() const
{
    return m_collider.getSize();
}
inline bool BoxCollider2D::Contains(const sf::Vector2f point) const
{
    return m_collider.getGlobalBounds().contains(point);
}

} // namespace xl
#endif // XLENGINE_BOXCOLLIDER2D_H
