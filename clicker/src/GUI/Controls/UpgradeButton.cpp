//
// Created by XL1TTE on 11.12.2025.
//

#include "GUI/Controls/UpgradeButton.h"

#include "G.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
UpgradeButton::UpgradeButton(const sf::Sprite &mesh, const std::string &upgrade)
    : LayoutObject(mesh), m_UpgradeID(upgrade)
{
}
sf::Vector2<float> UpgradeButton::GetSize() const
{
    return m_Mesh->getGlobalBounds().size;
}
bool UpgradeButton::Contains(sf::Vector2<float> point)
{
    return m_Mesh->getGlobalBounds().contains(point);
}
void UpgradeButton::OnPointerClick(const sf::Event::MouseButtonPressed &event)
{
    if (m_isActive == false)
    {
        return;
    }

    G::GetSession().AddGold(-1 * m_Stat.lock()->getCost());

    m_Stat.lock()->levelUp();
}
void UpgradeButton::OnPointerEnter(PointerEnterEvent event)
{
}
void UpgradeButton::Awake()
{
    m_Stat = G::GetSession().m_Stats[m_UpgradeID];

    this->SetActive(CanAffordBuy(G::GetSession().GetGold()));

    RegisterEvent<GoldChangedSignal>(
        [&](const GoldChangedSignal &signal)
        {
            this->SetActive(CanAffordBuy(signal.m_value));
        });
}

bool UpgradeButton::CanAffordBuy(const float &gold) const
{
    if (m_Stat.lock()->m_cost < gold)
    {
        return false;
    }
    return true;
}

void UpgradeButton::SetActive(const bool &isActive)
{
    if (isActive == false)
    {
        m_isActive = false;
        m_Mesh->setColor(sf::Color(255, 255, 255, 50));
    }
    else
    {
        m_isActive = true;
        m_Mesh->setColor(sf::Color(255, 255, 255, 255));
    }
}

void UpgradeButton::Draw(const std::weak_ptr<sf::RenderTarget> &weak_ptr)
{
    LayoutObject::Draw(weak_ptr);

    if (const std::shared_ptr<GameSession::IStat> stat = m_Stat.lock())
    {
        if (stat->isLevelCaped() == false)
        {
            weak_ptr.lock()->draw(*m_Mesh);
        }
    }
}