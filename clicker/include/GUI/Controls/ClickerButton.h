//
// Created by XL1TTE on 07.12.2025.
//
#ifndef EARN_POINT_BUTTON
#define EARN_POINT_BUTTON
#include "EventSystems/Events/IPointerClickHandler.h"
#include "EventSystems/Events/IPointerEnterHandler.h"
#include "RectangleButton.h"

class ClickerButton : public RectangleButton, public xl::IPointerEnterHandler, public xl::IPointerClickHandler
{

  public:
    ClickerButton()           = default;
    ~ClickerButton() override = default;

    sf::Vector2<float> GetSize() override;
    bool               Contains(sf::Vector2<float> point) override;

    void OnPointerClick(const sf::Event::MouseButtonPressed &event) override;
    void OnPointerEnter(PointerEnterEvent event) override;
};
#endif // EARN_POINT_BUTTON