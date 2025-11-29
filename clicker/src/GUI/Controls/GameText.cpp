//
// Created by XL1TTE on 29.11.2025.
//

#include "../../../include/GUI/Controls/GameText.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Text.hpp"

GameText::GameText(const sf::Font &font)
    : m_textView(std::make_unique<sf::Text>(font))
{
}
void GameText::Draw(const std::weak_ptr<sf::RenderTarget> &drawer)
{
    GameObject::Draw(drawer);

    if (m_linkedText.expired() == false)
    {
        SetText(*m_linkedText.lock());
    }

    AlignCenter();

    drawer.lock()->draw(*m_textView);
}
GameText &GameText::LinkText(const std::weak_ptr<std::string> &link)
{
    m_linkedText = link;
    return *this;
}
GameText &GameText::SetText(const std::string &text)
{
    m_textView->setString(text);
    return *this;
}
GameText &GameText::SetColor(const sf::Color color)
{
    m_textView->setFillColor(color);
    return *this;
}
GameText &GameText::SetFontSize(const unsigned int size)
{
    m_textView->setCharacterSize(size);
    return *this;
}
GameText &GameText::AlignCenter()
{
    if (m_parent.expired())
    {
        return *this;
    }

    const auto textBounds = m_textView->getLocalBounds();
    m_textView->setOrigin({textBounds.position.x + textBounds.size.x / 2.0f,
                           textBounds.position.y + textBounds.size.y / 2.0f});

    const auto [width, height] = m_parent.lock()->getSize();
    m_textView->setPosition({width / 2.0f, height / 2.0f});
    return *this;
}
sf::Vector2<float> GameText::getSize()
{
    return m_textView->getGlobalBounds().size;
}
sf::Vector2<float> GameText::getPosition()
{
    return m_textView->getPosition();
}
sf::Transform GameText::getTransform()
{
    return m_textView->getTransform();
}