//
// Created by XL1TTE on 29.11.2025.
//

#include "GUI/Controls/Container.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Transform.hpp"

Container::Container(const std::weak_ptr<sf::RectangleShape> &container)
    : m_container(container)
{
}
void Container::Draw(const std::weak_ptr<sf::RenderTarget> &drawer)
{
    GameObject::Draw(drawer);

    if (m_shouldFillWidth)
    {
        FillEmptyWidth();
    }

    drawer.lock()->draw(*m_container.lock());
}

sf::Transform Container::getTransform()
{
    return m_container.lock()->getTransform();
}
sf::Vector2<float> Container::getSize()
{
    return m_container.lock()->getSize();
}
sf::Vector2<float> Container::getPosition()
{
    return GameObject::getPosition();
}
Container &Container::FullWidth()
{
    m_shouldFillWidth = true;
    return *this;
}
void Container::FillEmptyWidth() const
{
    m_container.lock()->setSize(m_parent.lock()->getSize());
}