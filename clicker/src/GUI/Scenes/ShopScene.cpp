//
// Created by XL1TTE on 11.12.2025.
//

#include "Scenes/ShopScene.h"

#include "Controls/RootContainer.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "Controls/TextMesh.h"
#include "G.h"
#include "GUI/Controls/SceneSwitchButton.h"
#include "GUI/Controls/ShopItem.h"
#include "GUI/Fonts.h"
#include "Resources.h"
#include "Scenes/Scenes.h"

#include <ranges>

ShopScene::ShopScene(const std::weak_ptr<sf::RenderTarget> &renderer)
{
    const auto root = std::make_shared<xl::RootContainer>(renderer);

    auto goldText = std::make_shared<xl::TextMesh>(Fonts::FONT_DEFAULT);
    goldText->SetParent(root);
    goldText->SetColor(sf::Color::Yellow)
        .SetFontSize(32)
        .SetText(std::format("Balance: {0}", static_cast<int>(G::GetSession().GetGold())));

    goldText->Margin({32, 32});
    goldText->DefineLayout(
        {xl::Layout::HorizontalRight, xl::Layout::VerticalTop});

    constexpr float headerPad = 148;

    int index = -1;
    for (const auto &key : G::GetSession().m_Stats | std::views::keys)
    {
        constexpr float gap = 64.f;
        ++index;
        auto upgrade = std::make_shared<ShopItem>(
            sf::RectangleShape({root->GetSize().x - 20, 120.f}),
            *UP_POINTS_PER_CLICK(),
            key);

        upgrade->SetParent(root);
        upgrade->Margin({headerPad + static_cast<float>(index) * (200.f + gap), 0, 10, 10});
        upgrade->DefineLayout({xl::Layout::HorizontalLeft, xl::Layout::VerticalTop});

        WithObject(upgrade);
    }

    const auto toMainScene = std::make_shared<SceneSwitchButton>(*SPR_MAIN_SCENE_BUTTON(), MAIN_SCENE);
    toMainScene->SetParent(root);
    toMainScene->DefineLayout({xl::Layout::HorizontalCenter, xl::Layout::VerticalBottom});
    toMainScene->Margin({32, 0});

    RegisterEvent(xl::xlEngine::GetBus().subscribe<SceneSwitchRequest>(
        [renderer](const SceneSwitchRequest &signal)
        {
            Scenes::SwitchScene(renderer, signal.m_scene);
        }));

    RegisterEvent(xl::xlEngine::GetBus().subscribe<GoldChangedSignal>(
        [goldText](const GoldChangedSignal &signal)
        {
            goldText->SetText(std::format("Balance: {0}", static_cast<int>(G::GetSession().GetGold())));
        }));

    WithObject(root);
    WithObject(goldText);
    WithObject(toMainScene);
}
std::unique_ptr<xl::IGameScene> ShopScene::clone() const
{
    return std::make_unique<ShopScene>(*this);
}