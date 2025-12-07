#include "GUI/Scenes/MainScene.h"

#include "Controls/RootContainer.h"
#include "G.h"
#include "GUI/Controls/GameText.h"
#include "GUI/Fonts.h"
#include "Game.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "Signals/Signals.h"

//
// Created by XL1TTE on 29.11.2025.
//

MainScene::MainScene(const std::weak_ptr<sf::RenderTarget> &renderer)
{
    const auto root = std::make_shared<xl::RootContainer>(renderer);

    const auto goldText = std::make_shared<GameText>(Fonts::FONT_DEFAULT);

    goldText->SetParent(root);
    goldText->SetColor(sf::Color::Yellow)
        .SetFontSize(64)
        .SetText(std::to_string(G::GetGold()))
        .AlignCenter();

    RegisterEvent(
        Game::GetBus()
            .subscribe<GoldChangedSignal>(
                [goldText](const GoldChangedSignal &signal)
                {
                    goldText->SetText(std::to_string(signal.m_value));
                }));

    WithObject(root);
    WithObject(goldText);
}
std::unique_ptr<xl::IGameScene> MainScene::clone() const
{
    return std::make_unique<MainScene>(*this);
}