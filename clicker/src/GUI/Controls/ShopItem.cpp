//
// Created by XL1TTE on 12.12.2025.
//

#include "GUI/Controls/ShopItem.h"

#include "Controls/TextMesh.h"
#include "G.h"
#include "GUI/Controls/UpgradeButton.h"
#include "GUI/Fonts.h"
#include "Resources.h"
#include "SFML/Graphics/Sprite.hpp"

ShopItem::ShopItem(const sf::RectangleShape &mesh, const sf::Sprite &icon, std::string upgrade)
    : LayoutObject(mesh),
      m_ItemTooltip(std::make_unique<xl::TextMesh>(Fonts::FONT_DEFAULT)),
      m_ItemIcon(std::make_unique<LayoutObject<sf::Sprite>>(icon)),
      m_BuyButton(std::make_shared<UpgradeButton>(*SPR_BUY_BUTTON(), upgrade)),
      m_UpgradeId(std::move(upgrade))
{
}
void ShopItem::Awake()
{

    m_Mesh->setFillColor({130, 130, 130, 255});

    constexpr int gap = 8;

    m_ItemIcon->SetParent(shared_from_this());
    m_ItemIcon->DefineLayout({xl::Layout::VerticalCenter, xl::Layout::HorizontalLeft});
    m_ItemIcon->Margin({0, gap});

    m_ItemTooltip->SetParent(shared_from_this());
    m_ItemTooltip->DefineLayout({xl::Layout::VerticalCenter, xl::Layout::HorizontalLeft});
    m_ItemTooltip->Margin({0, gap + m_ItemIcon->GetSize().x});

    m_BuyButton->SetParent(shared_from_this());
    m_BuyButton->DefineLayout({xl::Layout::VerticalCenter, xl::Layout::HorizontalRight});
    m_BuyButton->Margin({0, 32});
    m_BuyButton->OnClick([&]
                         { m_ItemTooltip->SetText(std::format("Name: {0}\nCost: {1}\nLevel: {2}/{3}\nPower:{4}",
                                                              m_UpgradeId, m_Stat->getCost(), m_Stat->m_level, m_Stat->m_maxLevel, m_Stat->value())); });

    xl::xlEngine::Get()
        .SpawnObject(m_BuyButton); // <-- makes button available to event system
                                   //     and delegate render to current scene.

    m_Stat = G::GetSession().m_Stats[m_UpgradeId];
    m_ItemTooltip->SetText(std::format("Name: {0}\nCost: {1}\nLevel: {2}/{3}\nPower: {4}",
                                       m_UpgradeId, m_Stat->getCost(), m_Stat->m_level, m_Stat->m_maxLevel, m_Stat->value()));
}

void ShopItem::Draw(const std::weak_ptr<sf::RenderTarget> &weak_ptr)
{
    ApplyAllStyles();
    LayoutObject::Draw(weak_ptr);

    m_ItemIcon->ApplyAllStyles();
    m_ItemIcon->Draw(weak_ptr);
    m_ItemTooltip->Draw(weak_ptr);
    // m_BuyButton->Draw(weak_ptr);
}

sf::Vector2<float> ShopItem::GetSize() const
{
    return m_Mesh->getGlobalBounds().size;
}
