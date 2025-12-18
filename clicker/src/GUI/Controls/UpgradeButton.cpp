//
// Created by XL1TTE on 11.12.2025.
//

#include <utility>

#include "G.h"
#include "GUI/Controls/UpgradeButton.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"

UpgradeButton::UpgradeButton(const sf::Sprite &mesh, std::string upgrade)
    : LayoutObject(mesh),
      m_UpgradeID(std::move(upgrade))
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

    UpdateState();

    m_OnClick();
}
void UpgradeButton::OnPointerEnter(PointerEnterEvent event)
{
}
void UpgradeButton::Awake()
{
    m_Stat = G::GetSession().m_Stats[m_UpgradeID];

    UpdateState();
}

void UpgradeButton::UpdateState()
{
    this->SetActive(CanAffordBuy(G::GetSession().GetGold()));
}

bool UpgradeButton::CanAffordBuy(const float &gold) const
{
    // std::cout << std::format("Cost: {0}, Gold: {1}", m_Stat.lock()->getCost(), gold) << std::endl;
    if (m_Stat.lock()->getCost() > gold)
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
    UpdateState();
    if (m_Stat.lock()->isLevelCaped())
    {
        return;
    }
    ApplyAllStyles();
    weak_ptr.lock()->draw(*m_Mesh);
}
void UpgradeButton::OnClick(const std::function<void()> &handler)
{
    m_OnClick = handler;
}