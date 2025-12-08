//
// Created by XL1TTE on 29.11.2025.
//

#include "Behaviour/GameObject.h"
#include "SFML/Graphics/Transform.hpp"
#include "SFML/System/Vector2.hpp"

using namespace xl;

void GameObject::Awake()
{
}
void GameObject::Update(const int32_t &dt)
{
}
void GameObject::Destroy()
{
}
void GameObject::Draw(const std::weak_ptr<sf::RenderTarget> &drawer)
{
}
sf::Vector2f GameObject::GetSize() const
{
    return {0.f, 0.f};
}
sf::Vector2<float> GameObject::GetPosition() const
{
    return {0.f, 0.f};
}
sf::Transform GameObject::GetTransform() const
{
    return sf::Transform::Identity;
}

void GameObject::SetParent(const std::weak_ptr<GameObject> &parent)
{
    m_parent = parent;
}
