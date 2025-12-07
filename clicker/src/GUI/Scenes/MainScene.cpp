#include "GUI/Scenes/MainScene.h"

#include "Controls/RootContainer.h"
#include "G.h"
#include "GUI/Controls/ClickerButton.h"
#include "GUI/Controls/GameText.h"
#include "GUI/Controls/RectangleButton.h"
#include "GUI/Fonts.h"
#include "SFML/Graphics.hpp"
#include "Signals/Signals.h"
#include "XL_ENGINE_H"

#include <memory>

//
// Created by XL1TTE on 29.11.2025.
//

MainScene::MainScene(const std::weak_ptr<sf::RenderTarget> &renderer)
{
    const auto root = std::make_shared<xl::RootContainer>(renderer);

    const auto clickerButton = std::make_shared<ClickerButton>();
    clickerButton->SetParent(root);
    clickerButton->AlignCenter();

    auto goldText = std::make_unique<GameText>(Fonts::FONT_DEFAULT);
    goldText->SetParent(clickerButton);
    goldText->SetColor(sf::Color::Yellow)
        .SetFontSize(64)
        .SetText(std::to_string(G::GetGold()))
        .AlignCenter();

    clickerButton->SetLabel(goldText);

    RegisterEvent(
        xl::xlEngine::GetBus()
            .subscribe<GoldChangedSignal>(
                [clickerButton](const GoldChangedSignal &signal)
                {
                    clickerButton->ChangeText(std::to_string(signal.m_value));
                }));

    WithObject(root);
    WithObject(clickerButton);
}
std::unique_ptr<xl::IGameScene> MainScene::clone() const
{
    return std::make_unique<MainScene>(*this);
}