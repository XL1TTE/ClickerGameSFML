//
// Created by XL1TTE on 07.12.2025.
//

#include "GUI/Controls/ClickerButton.h"

#include "Controls/TextMesh.h"
#include "G.h"
#include "SignalBus/SignalBus.h"
#include "Signals/Signals.h"
#include "xlEngine.h"

ClickerButton::ClickerButton(const sf::RectangleShape &mesh)
    : RectangleButton(mesh)
{
}
bool ClickerButton::Contains(const sf::Vector2<float> point)
{
    return RectangleButton::m_Mesh->getGlobalBounds().contains(point);
}
void ClickerButton::OnPointerClick(const sf::Event::MouseButtonPressed &event)
{
    G::GetSession().AddGold(1);
    xl::xlEngine::GetBus().emit(GoldChangedSignal(G::GetSession().GetGold()));
}
void ClickerButton::OnPointerEnter(PointerEnterEvent event)
{
    m_label->SetColor(sf::Color::Black);
    m_Mesh->setFillColor(sf::Color::White);
}
void ClickerButton::OnPointerExit(PointerExitEvent event)
{
    m_label->SetColor(sf::Color::White);
    m_Mesh->setFillColor(sf::Color::Blue);
}
sf::Vector2<float> ClickerButton::GetSize()
{
    return m_Mesh->getGlobalBounds().size;
}