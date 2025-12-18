//
// Created by XL1TTE on 11.12.2025.
//

#include "GUI/Controls/HealthBar.h"

#include "G.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SignalBus/SignalBus.h"
#include "Signals/Signals.h"
#include "xlEngine.h"

HealthBar::HealthBar(const sf::RectangleShape &mesh, const float start)
    : LayoutObject(mesh), m_fillArea(std::make_unique<sf::RectangleShape>())
{
    auto [pW, pH] = GetSize();
    m_fillArea->setSize({pW * start, pH});
    m_fillArea->setFillColor(sf::Color::Red);
}
sf::Vector2<float> HealthBar::GetSize() const
{
    return m_Mesh->getGlobalBounds().size;
}
void HealthBar::Draw(const std::weak_ptr<sf::RenderTarget> &weak_ptr)
{
    ApplyAllStyles(); // <-- Layouts

    m_fillArea->setOrigin(m_Mesh->getOrigin());
    m_fillArea->setPosition(m_Mesh->getPosition());

    weak_ptr.lock()->draw(*m_Mesh);
    weak_ptr.lock()->draw(*m_fillArea);
}
void HealthBar::Awake()
{
    RegisterEvent<PlayerHealthChanged>(
        [&](const PlayerHealthChanged &signal)
        { OnPlayerHealthChanged(signal); });

    auto [x, y]     = m_fillArea->getSize();
    auto [bgX, bgY] = m_Mesh->getSize();
    m_fillArea->setSize({bgX * G::GetSession().GetHealthPercent(), y});
}

void HealthBar::OnPlayerHealthChanged(const PlayerHealthChanged &signal) const
{
    auto [x, y]     = m_fillArea->getSize();
    auto [bgX, bgY] = m_Mesh->getSize();
    m_fillArea->setSize({bgX * signal.m_healthPercent, y});
}