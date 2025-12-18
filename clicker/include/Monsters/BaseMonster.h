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
                          public xl::IPointerClickHandler
{
  public:
    explicit BaseMonster(const sf::Sprite &sprite, float damage, float cooldown, int speed);
    BaseMonster(const BaseMonster &other);

    void Awake() override;
    void Update(float dt) override;
    void Move(float dt);

    bool isDied;
    int  m_speed;

  protected:
    float m_TimeLeft;
    float m_AttackDamage;
    float m_AttackCooldown;

    void Attack() const;

  public:
    bool                             Contains(sf::Vector2<float> point) override;
    void                             OnPointerClick(const sf::Event::MouseButtonPressed &event) override;
    void                             Die();
    void                             OnPointerEnter(PointerEnterEvent event) override;
    void                             Draw(const std::weak_ptr<sf::RenderTarget> &) override;
    [[nodiscard]] sf::Vector2<float> GetSize() const override;
};

#endif // CLICKER_BASEMONSTER_H
