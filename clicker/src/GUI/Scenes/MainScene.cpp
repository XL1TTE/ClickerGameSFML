#include "GUI/Scenes/MainScene.h"

#include "Controls/LayoutObject.h"
#include "Controls/RectangleButton.h"
#include "Controls/RootContainer.h"
#include "Controls/TextMesh.h"
#include "G.h"
#include "GUI/Controls/ClickerButton.h"
#include "GUI/Controls/MonsterSpawner.h"
#include "GUI/Fonts.h"
#include "Monsters/BaseMonster.h"
#include "Resources.h"
#include "SFML/Graphics.hpp"
#include "Scenes/Scenes.h"
#include "Signals/Signals.h"
#include "XL_ENGINE_H"

#include <memory>

//
// Created by XL1TTE on 29.11.2025.
//

MainScene::MainScene(const std::weak_ptr<sf::RenderTarget> &renderer)
{
    const auto root = std::make_shared<xl::RootContainer>(renderer);

    const auto clickerButton = std::make_shared<ClickerButton>(sf::RectangleShape({200.f, 100.f}));

    clickerButton->SetLabel("Click", Fonts::FONT_DEFAULT);

    clickerButton->SetParent(root);
    clickerButton->DefineLayout(
        {xl::Layout::HorizontalCenter, xl::Layout::VerticalBottom});
    clickerButton->Margin({32, 0});

    auto goldText = std::make_shared<xl::TextMesh>(Fonts::FONT_DEFAULT);
    goldText->SetParent(root);
    goldText->SetColor(sf::Color::Yellow)
        .SetFontSize(64)
        .SetText(std::to_string(G::GetSession().GetGold()));

    goldText->Margin({32, 32});
    goldText->DefineLayout(
        {xl::Layout::HorizontalRight, xl::Layout::VerticalTop});

    auto monsterSpawner = std::make_shared<MonsterSpawner>(
        MonsterSpawner(root, 2,
                       BaseMonster(*SPR_MONSTER(), 1, 3)));

    RegisterEvent(xl::xlEngine::GetBus().subscribe<GoldChangedSignal>(
        [goldText, renderer](const GoldChangedSignal &signal)
        {
            goldText->SetText(std::to_string(signal.m_value));
        }));

    WithObject(root);
    WithObject(goldText);
    WithObject(clickerButton);
    WithObject(monsterSpawner);
}
std::unique_ptr<xl::IGameScene> MainScene::clone() const
{
    return std::make_unique<MainScene>(*this);
}