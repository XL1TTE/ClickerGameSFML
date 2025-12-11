//
// Created by XL1TTE on 11.12.2025.
//

#ifndef CLICKER_HEALTHBAR_H
#define CLICKER_HEALTHBAR_H
#include "Controls/LayoutObject.h"
#include "SignalBus/SignalBus.h"

class PlayerHealthChanged;
namespace sf
{
class RectangleShape;
}
class HealthBar final : public xl::LayoutObject<sf::RectangleShape>
{
  public:
    explicit HealthBar(const sf::RectangleShape &mesh, float start = 1.f);
    ~HealthBar() override = default;

    [[nodiscard]] sf::Vector2<float> GetSize() const override;
    void                             Draw(const std::weak_ptr<sf::RenderTarget> &) override;

    void Awake() override;

  private:
    void OnPlayerHealthChanged(const PlayerHealthChanged &signal) const;

    std::unique_ptr<sf::RectangleShape> m_fillArea;
};

#endif // CLICKER_HEALTHBAR_H
