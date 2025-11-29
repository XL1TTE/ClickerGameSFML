#include "GUI/Scenes/MainScene.h"

#include "GUI/Controls/GameText.h"
#include "GUI/Controls/RootContainer.h"
#include "GUI/Fonts.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

//
// Created by XL1TTE on 29.11.2025.
//

MainScene::MainScene(const std::weak_ptr<sf::RenderTarget> &renderer)
    : m_goldText(std::make_shared<std::string>())
{
    auto root = std::make_shared<RootContainer>(renderer);

    auto goldText = std::make_shared<GameText>(Fonts::FONT_DEFAULT);

    goldText->SetParent(root);
    goldText->SetColor(sf::Color::Yellow)
        .LinkText(m_goldText)
        .SetFontSize(64)
        .AlignCenter();

    *m_goldText = std::to_string(m_gold);

    WithObject(root);
    WithObject(goldText);
}

void MainScene::AddGold(const uint32_t amount)
{
    m_gold += amount;
    if (m_goldText)
    {
        *m_goldText = std::to_string(m_gold);
    }
}