//
// Created by XL1TTE on 07.12.2025.
//
#ifndef EARN_POINT_BUTTON
#define EARN_POINT_BUTTON
#include "Controls/Button.h"
#include "EventSystems/Events/IPointerClickHandler.h"
#include "EventSystems/Events/IPointerEnterHandler.h"

class ClickerButton final : public xl::Button, public xl::IPointerEnterHandler, public xl::IPointerClickHandler
{
  public:
    explicit ClickerButton(std::unique_ptr<sf::Shape> &&mesh);
    ~ClickerButton() override = default;

    bool Contains(sf::Vector2<float> point) override;

    void               OnPointerClick(const sf::Event::MouseButtonPressed &event) override;
    void               OnPointerEnter(PointerEnterEvent event) override;
    sf::Vector2<float> GetSize() override;
};
#endif // EARN_POINT_BUTTON