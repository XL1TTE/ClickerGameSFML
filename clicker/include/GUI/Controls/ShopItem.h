//
// Created by XL1TTE on 12.12.2025.
//

#ifndef CLICKER_SHOPITEM_H
#define CLICKER_SHOPITEM_H
#include "Controls/LayoutObject.h"
#include "Data/GameSession.h"
#include "EventSystems/Events/IPointerClickHandler.h"
#include "EventSystems/Events/IPointerEnterHandler.h"

namespace sf
{
class Sprite;
}
namespace xl
{
class TextMesh;
}
class UpgradeButton;
namespace sf
{
class RectangleShape;
}
class ShopItem final : public xl::LayoutObject<sf::RectangleShape>
{
  public:
    explicit ShopItem(const sf::RectangleShape &mesh, const sf::Sprite &icon, std::string upgrade);

    std::unique_ptr<xl::TextMesh>             m_ItemTooltip;
    std::unique_ptr<LayoutObject<sf::Sprite>> m_ItemIcon;
    std::shared_ptr<UpgradeButton>            m_BuyButton;
    std::string                               m_UpgradeId;
    std::shared_ptr<GameSession::IStat>       m_Stat;

    void Awake() override;

    void Draw(const std::weak_ptr<sf::RenderTarget> &) override;

    [[nodiscard]] sf::Vector2<float> GetSize() const override;
};

#endif // CLICKER_SHOPITEM_H
