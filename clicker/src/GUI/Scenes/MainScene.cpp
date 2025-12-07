#include "GUI/Scenes/MainScene.h"

#include "Controls/Button.h"
#include "Controls/LayoutObject.h"
#include "Controls/RootContainer.h"
#include "Controls/TextMesh.h"
#include "G.h"
#include "GUI/Controls/ClickerButton.h"
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

    std::unique_ptr<sf::RectangleShape> button_rect   = std::make_unique<sf::RectangleShape>(sf::Vector2f(200.f, 200.f));
    const auto                          clickerButton = std::make_shared<ClickerButton>(std::move(button_rect));

    clickerButton->SetParent(root);
    clickerButton->HorizontalCenter();
    clickerButton->VerticalBottom();

    auto goldText = std::make_shared<xl::TextMesh>(Fonts::FONT_DEFAULT);
    goldText->SetParent(root);
    goldText->SetColor(sf::Color::Yellow)
        .SetFontSize(64)
        .SetText(std::to_string(G::GetGold()));

    goldText->HorizontalCenter();
    goldText->VerticalTop();

    clickerButton->SetLabel(clickerButton, "Click", Fonts::FONT_DEFAULT);

    RegisterEvent(
        xl::xlEngine::GetBus()
            .subscribe<GoldChangedSignal>(
                [goldText](const GoldChangedSignal &signal)
                {
                    goldText->SetText(std::to_string(signal.m_value));
                }));

    WithObject(root);
    WithObject(goldText);
    WithObject(clickerButton);
}
std::unique_ptr<xl::IGameScene> MainScene::clone() const
{
    return std::make_unique<MainScene>(*this);
}