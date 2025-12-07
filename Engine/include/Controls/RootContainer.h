//
// Created by XL1TTE on 29.11.2025.
//

#ifndef XLENGINE_ROOTCONTAINER_H
#define XLENGINE_ROOTCONTAINER_H
#include "Behaviour/GameObject.h"

namespace xl
{

class RootContainer final : public GameObject
{
  public:
    explicit RootContainer(const std::weak_ptr<sf::RenderTarget> &);

  protected:
    std::weak_ptr<sf::RenderTarget> m_root;

  public:
    sf::Transform      GetTransform() const override;
    sf::Vector2<float> GetSize() const override;
    sf::Vector2<float> GetPosition() const override;
};
} // namespace xl
#endif // XLENGINE_ROOTCONTAINER_H
