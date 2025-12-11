//
// Created by XL1TTE on 09.12.2025.
//

#ifndef CLICKER_BASEMONSTER_H
#define CLICKER_BASEMONSTER_H
#include "Controls/RectangleButton.h"
#include "EventSystems/Events/IPointerClickHandler.h"
#include "EventSystems/Events/IPointerEnterHandler.h"

namespace sf
{
class Sprite;
}
class BaseMonster final : public xl::LayoutObject<sf::Sprite>,
                          public xl::IPointerEnterHandler,
                          public xl::IPointerClickHandler,
                          public std::enable_shared_from_this<BaseMonster>
{
  public:
    explicit BaseMonster(const sf::Sprite &sprite, const float damage, const float cooldown);
    BaseMonster(const BaseMonster &other);

    void Update(const float dt) override;

    bool isDied;

  protected:
    float m_TimeLeft;
    float m_AttackDamage;
    float m_AttackCooldown;

    void Attack() const;

  public:
    sf::Vector2<float> GetSize() override;
    bool               Contains(sf::Vector2<float> point) override;
    void               OnPointerClick(const sf::Event::MouseButtonPressed &event) override;
    void               OnPointerEnter(PointerEnterEvent event) override;
    void               Draw(const std::weak_ptr<sf::RenderTarget> &) override;
};

#endif // CLICKER_BASEMONSTER_H
