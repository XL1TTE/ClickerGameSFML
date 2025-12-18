#include "Scenes/MainScene.h"
#include "Controls/LayoutObject.h"
#include "Controls/RectangleButton.h"
#include "Controls/RootContainer.h"
#include "Controls/TextMesh.h"
#include "G.h"
#include "GUI/Controls/ClickerButton.h"
#include "GUI/Controls/HealthBar.h"
#include "GUI/Controls/MonsterSpawner.h"
#include "GUI/Controls/SceneSwitchButton.h"
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
        .SetText(std::to_string(static_cast<int>(G::GetSession().GetGold())));

    goldText->Margin({32, 32});
    goldText->DefineLayout(
        {xl::Layout::HorizontalRight, xl::Layout::VerticalTop});

    auto monsterSpawner = std::make_shared<MonsterSpawner>(
        MonsterSpawner(root, 5.f, 10.f,
                       BaseMonster(*SPR_MONSTER(), 5, 3)));

    const auto healthBar = std::make_shared<HealthBar>(sf::RectangleShape({128.f, 32.f}));
    healthBar->SetParent(root);
    healthBar->DefineLayout({xl::Layout::VerticalBottom, xl::Layout::HorizontalLeft});
    healthBar->Margin({32, 32});

    auto toShop = std::make_shared<SceneSwitchButton>(*SPR_TO_SHOP_BUTTON(), SHOP_SCENE);
    toShop->SetParent(root);
    toShop->DefineLayout({xl::Layout::HorizontalRight, xl::Layout::VerticalBottom});
    toShop->Margin({32, 32});

    RegisterEvent(xl::xlEngine::GetBus().subscribe<GoldChangedSignal>(
        [goldText](const GoldChangedSignal &signal)
        {
            goldText->SetText(std::to_string(static_cast<int>(signal.m_value)));
        }));
    RegisterEvent(xl::xlEngine::GetBus().subscribe<MonsterAttackedSignal>(
        [](const MonsterAttackedSignal &signal)
        {
            G::GetSession().AddHealth(signal.m_damage * -1);
        }));
    RegisterEvent(xl::xlEngine::GetBus().subscribe<PlayerHealthChanged>(
        [healthBar](const PlayerHealthChanged &signal)
        {
            if (signal.m_health <= 0)
            {
                xl::xlEngine::DestroyObject(healthBar);
                // xl::xlEngine::Exit();
            }
        }));
    RegisterEvent(xl::xlEngine::GetBus().subscribe<SceneSwitchRequest>(
        [renderer](const SceneSwitchRequest &signal)
        {
            Scenes::SwitchScene(renderer, signal.m_scene);
        }));

    WithObject(root);
    WithObject(goldText);
    WithObject(clickerButton);
    WithObject(healthBar);
    WithObject(monsterSpawner);
    WithObject(toShop);
}
void MainScene::OnAwake()
{
    m_gold_per_second = G::GetSession().m_Stats["gold_per_second"];
}
void MainScene::OnUpdate(float dt)
{
    if (m_timer >= 1.f)
    {
        G::GetSession().AddGold(m_gold_per_second->value());
        m_timer = 0.f;
    }
    m_timer += dt;
}

std::unique_ptr<xl::IGameScene> MainScene::clone() const
{
    return std::make_unique<MainScene>(*this);
}