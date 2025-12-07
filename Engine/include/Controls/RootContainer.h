//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_ROOTCONTAINER_H
#define CLICKER_ROOTCONTAINER_H
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
    sf::Transform      getTransform() override;
    sf::Vector2<float> getSize() override;
    sf::Vector2<float> getPosition() override;
};

#endif // CLICKER_ROOTCONTAINER_H
}