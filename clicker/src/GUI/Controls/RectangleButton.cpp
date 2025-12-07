//
// Created by XL1TTE on 07.12.2025.
//

#include "GUI/Controls/RectangleButton.h"

#include "GUI/Controls/GameText.h"
#include "GUI/Fonts.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"

RectangleButton::RectangleButton()
{
    m_button = std::make_unique<sf::RectangleShape>(sf::Vector2f(200.f, 100.f));
    m_button->setFillColor(sf::Color::Blue);
}
RectangleButton::~RectangleButton()
{
}

RectangleButton &RectangleButton::AlignCenter()
{
    if (m_parent.expired())
    {
        return *this;
    }

    const auto textBounds = m_button->getLocalBounds();
    m_button->setOrigin({textBounds.position.x + textBounds.size.x / 2.0f,
                         textBounds.position.y + textBounds.size.y / 2.0f});

    const auto [parentX, parentY] = m_parent.lock()->getPosition();
    const auto [parentW, parentH] = m_parent.lock()->GetSize();
    m_button->setPosition({parentX, parentY});
    return *this;
}
void RectangleButton::SetLabel(std::unique_ptr<GameText> &label)
{
    m_label = std::move(label);
    m_label->AlignCenter();
}
void RectangleButton::ChangeText(const std::string &text) const
{
    if (m_label != nullptr)
    {
        m_label->SetText(text);
    }
}
sf::Vector2<float> RectangleButton::getPosition()
{
    return m_button->getPosition();
}
sf::Vector2<float> RectangleButton::GetSize()
{
    return sf::Vector2f(200.f, 100.f);
}

void RectangleButton::Draw(const std::weak_ptr<sf::RenderTarget> &weak_ptr)
{
    if (const auto renderer = weak_ptr.lock())
    {
        renderer->draw(*m_button);
        m_label->Draw(weak_ptr);
    }
}