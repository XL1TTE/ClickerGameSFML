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
BaseMonster::BaseMonster(const sf::Sprite &sprite, const float damage, const float cooldown)
    : LayoutObject(sprite), isDied(false),
      m_TimeLeft(cooldown),
      m_AttackDamage(damage),
      m_AttackCooldown(cooldown)
{
}
BaseMonster::BaseMonster(const BaseMonster &other)
    : LayoutObject(*other.m_Mesh),
      isDied(false), m_TimeLeft(other.m_TimeLeft),
      m_AttackDamage(other.m_AttackDamage),
      m_AttackCooldown(other.m_AttackCooldown)
{
}
void BaseMonster::Update(const float dt)
{
    if (m_TimeLeft <= 0)
    {
        Attack();
        m_TimeLeft = m_AttackCooldown;
    }
    m_TimeLeft -= dt;
}
void BaseMonster::Attack() const
{
    xl::xlEngine::GetBus().emit(MonsterAttackedSignal(m_AttackDamage));
}
sf::Vector2<float> BaseMonster::GetSize() const
{
    return m_Mesh->getGlobalBounds().size;
}
bool BaseMonster::Contains(sf::Vector2<float> point)
{
    return m_Mesh->getGlobalBounds().contains(point);
}

void BaseMonster::OnPointerClick(const sf::Event::MouseButtonPressed &event)
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
    LayoutObject<sf::Sprite>::Draw(weak_ptr);
    weak_ptr.lock()->draw(*m_Mesh);
}
