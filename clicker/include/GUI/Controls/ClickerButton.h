//
// Created by XL1TTE on 07.12.2025.
//
#ifndef EARN_POINT_BUTTON
#define EARN_POINT_BUTTON
#include "Controls/RectangleButton.h"
#include "EventSystems/Events/IPointerClickHandler.h"
#include "EventSystems/Events/IPointerEnterHandler.h"
#include "EventSystems/Events/IPointerExitHandler.h"

class ClickerButton final : public xl::RectangleButton,
                            public xl::IPointerEnterHandler,
                            public xl::IPointerExitHandler,
                            public xl::IPointerClickHandler
{
  public:
    explicit ClickerButton(const sf::RectangleShape &mesh);
    ~ClickerButton() override = default;

    bool Contains(sf::Vector2<float> point) override;

    void               OnPointerClick(const sf::Event::MouseButtonPressed &event) override;
    void               OnPointerEnter(PointerEnterEvent event) override;
    void               OnPointerExit(PointerExitEvent event) override;
    sf::Vector2<float> GetSize() const override;
};
#endif // EARN_POINT_BUTTON