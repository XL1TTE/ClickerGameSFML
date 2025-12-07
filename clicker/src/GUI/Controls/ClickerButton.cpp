//
// Created by XL1TTE on 07.12.2025.
//

#include "GUI/Controls/ClickerButton.h"

#include "G.h"
#include "SignalBus/SignalBus.h"
#include "Signals/Signals.h"
#include "xlEngine.h"

sf::Vector2<float> ClickerButton::GetSize()
{
    return RectangleButton::GetSize();
}
bool ClickerButton::Contains(const sf::Vector2<float> point)
{
    return RectangleButton::m_button->getGlobalBounds().contains(point);
}
void ClickerButton::OnPointerClick(const sf::Event::MouseButtonPressed &event)
{
    G::AddGold(1);
    xl::xlEngine::GetBus().emit(GoldChangedSignal(G::GetGold()));
}
void ClickerButton::OnPointerEnter(PointerEnterEvent event)
{
}