#include "GUI/Scenes/MainScene.h"

#include "GUI/Fonts.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

//
// Created by XL1TTE on 29.11.2025.
//

MainScene::MainScene()
    : m_goldText(std::make_shared<sf::Text>(Fonts::FONT_DEFAULT))
{
    m_goldText->setFillColor(sf::Color::Yellow);
    m_goldText->setCharacterSize(32);
    m_goldText->setString(std::to_string(m_gold));
    const auto textBounds = m_goldText->getGlobalBounds();
    m_goldText->setOrigin({textBounds.position.x + textBounds.size.x / 2.0f,
                           textBounds.position.y + textBounds.size.y / 2.0f});
}

void MainScene::Render(const std::weak_ptr<sf::RenderWindow> &weak_ptr)
{
    IGameScene::Render(weak_ptr);
    const auto window = weak_ptr.lock();

    auto [width, height] = sf::Vector2f(window->getView().getSize());

    m_goldText->setPosition({width / 2.0f, 0 + m_goldText->getGlobalBounds().size.y + 5.f / 2.0f});

    window->draw(*m_goldText);
}
void MainScene::AddGold(const uint32_t amount)
{
    m_gold += amount;
    m_goldText->setString(std::to_string(m_gold));
}