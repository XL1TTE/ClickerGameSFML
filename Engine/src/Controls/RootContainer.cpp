//
// Created by XL1TTE on 29.11.2025.
//

#include "Controls/RootContainer.h"
#include "SFML/Graphics/RenderTarget.hpp"

using namespace xl;

RootContainer::RootContainer(const std::weak_ptr<sf::RenderTarget> &renderer)
    : m_root(renderer)
{
}
sf::Transform RootContainer::getTransform()
{
    if (m_root.expired())
    {
        return GameObject::getTransform();
    }
    return m_root.lock()->getView().getTransform();
}
sf::Vector2<float> RootContainer::GetSize()
{
    if (m_root.expired())
    {
        return GameObject::GetSize();
    }
    return m_root.lock()->getView().getSize();
}
sf::Vector2<float> RootContainer::getPosition()
{
    if (m_root.expired())
    {
        return GameObject::getPosition();
    }
    return m_root.lock()->getView().getCenter();
}