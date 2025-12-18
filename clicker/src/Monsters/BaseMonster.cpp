//
// Created by XL1TTE on 09.12.2025.
//

#include "Monsters/BaseMonster.h"
#include "EventSystems/Events/IPointerEnterHandler.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SignalBus/SignalBus.h"
#include "Signals/Signals.h"
#include "xlEngine.h"
BaseMonster::BaseMonster(const sf::Sprite &sprite, const float damage, const float cooldown, const int speed)
    : LayoutObject(sprite), isDied(false),
      m_TimeLeft(cooldown),
      m_speed(speed),
      m_AttackDamage(damage),
      m_AttackCooldown(cooldown)
{
}
BaseMonster::BaseMonster(const BaseMonster &other)
    : LayoutObject(*other.m_Mesh),
      isDied(false), m_TimeLeft(other.m_TimeLeft),
      m_AttackDamage(other.m_AttackDamage),
      m_speed(other.m_speed),
      m_AttackCooldown(other.m_AttackCooldown)
{
}
void BaseMonster::Awake()
{
    ApplyAllStyles();
}
void BaseMonster::Update(const float dt)
{
    // Move(dt);
    if (m_TimeLeft <= 0)
    {
        Attack();
        m_TimeLeft = m_AttackCooldown;
    }
    m_TimeLeft -= dt;
}
void BaseMonster::Move(const float dt)
{
    float x = xl::xlEngine::Math::RandFloat(-2, 2);
    m_Mesh->move({x * m_speed * dt, m_speed * dt});
    auto parent = m_parent.lock();
    auto maxY   = parent->GetPosition().y + parent->GetSize().y / 2;
    if (m_Mesh->getPosition().y > maxY)
    {
        Die();
    }
}
void BaseMonster::Attack() const
{
    xl::xlEngine::GetBus().emit(MonsterAttackedSignal(m_AttackDamage));
}
bool BaseMonster::Contains(sf::Vector2<float> point)
{
    return m_Mesh->getGlobalBounds().contains(point);
}
void BaseMonster::OnPointerClick(const sf::Event::MouseButtonPressed &event)
{
    Die();
}

void BaseMonster::Die()
{
    isDied = true;
    std::cout << "Enemy is died" << std::endl;
    xl::xlEngine::DestroyObject(shared_from_this());
}

void BaseMonster::OnPointerEnter(PointerEnterEvent event)
{
}

void BaseMonster::Draw(const std::weak_ptr<sf::RenderTarget> &weak_ptr)
{
    ApplyAllStyles();
    weak_ptr.lock()->draw(*m_Mesh);
}
sf::Vector2<float> BaseMonster::GetSize() const
{
    return m_Mesh->getGlobalBounds().size;
}
