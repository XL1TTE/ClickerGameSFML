//
// Created by XL1TTE on 11.12.2025.
//

#ifndef CLICKER_BUYBUTTON_H
#define CLICKER_BUYBUTTON_H
#include "Controls/RectangleButton.h"
#include "Data/GameSession.h"
#include "Data/Upgrades.h"
#include "EventSystems/Events/IPointerClickHandler.h"
#include "EventSystems/Events/IPointerEnterHandler.h"

namespace sf
{
class Sprite;
}
class UpgradeButton final : public xl::LayoutObject<sf::Sprite>,
                            public xl::IPointerEnterHandler,
                            public xl::IPointerClickHandler
{
  public:
    explicit UpgradeButton(const sf::Sprite &mesh, std::string upgrade);

    [[nodiscard]] sf::Vector2<float> GetSize() const override;
    bool                             Contains(sf::Vector2<float> point) override;
    void                             OnPointerClick(const sf::Event::MouseButtonPressed &event) override;
    void                             OnPointerEnter(PointerEnterEvent event) override;

    void               Awake() override;
    void               UpdateState();
    [[nodiscard]] bool CanAffordBuy(const float &gold) const;
    void               SetActive(const bool &isActive);
    void               Draw(const std::weak_ptr<sf::RenderTarget> &) override;

    void OnClick(const std::function<void()> &);

    std::string m_UpgradeID;

  protected:
    bool                              m_isActive = false;
    std::weak_ptr<GameSession::IStat> m_Stat;
    std::function<void()>             m_OnClick;
};

#endif // CLICKER_BUYBUTTON_H
