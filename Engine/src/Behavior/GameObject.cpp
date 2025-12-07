//
// Created by XL1TTE on 29.11.2025.
//

#include "Behaviour/GameObject.h"
#include "SFML/Graphics/Transform.hpp"
#include "SFML/System/Vector2.hpp"

using namespace xl;

void GameObject::Awake()
{
    for (auto &child : m_childrens)
    {
        child.lock()->Awake();
    }
}
void GameObject::Update(const int32_t &dt)
{
    for (auto &child : m_childrens)
    {
        child.lock()->Update(dt);
    }
}
void GameObject::Destroy()
{
    for (auto &child : m_childrens)
    {
        child.lock()->Destroy();
    }
}
void GameObject::Draw(const std::weak_ptr<sf::RenderTarget> &drawer)
{
    for (auto &child : m_childrens)
    {
        child.lock()->Draw(drawer);
    }
}
sf::Vector2f GameObject::getSize()
{
    return {0.f, 0.f};
}
sf::Vector2<float> GameObject::getPosition()
{
    return {0.f, 0.f};
}
sf::Transform GameObject::getTransform()
{
    return sf::Transform::Identity;
}
void GameObject::SetParent(const std::weak_ptr<GameObject> &parent)
{
    m_parent = parent;
}