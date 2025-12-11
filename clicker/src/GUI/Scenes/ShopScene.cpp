//
// Created by XL1TTE on 11.12.2025.
//

#include "Scenes/ShopScene.h"

#include "Controls/RootContainer.h"
#include "G.h"
#include "GUI/Controls/SceneSwitchButton.h"
#include "GUI/Controls/UpgradeButton.h"
#include "GUI/Fonts.h"
#include "Resources.h"
#include "Scenes/Scenes.h"

#include <ranges>

ShopScene::ShopScene(const std::weak_ptr<sf::RenderTarget> &renderer)
{
    const auto root = std::make_shared<xl::RootContainer>(renderer);

    const float gap   = 10.f;
    int         index = 0;
    for (const auto key : G::GetSession().m_Stats | std::views::keys)
    {
        ++index;
        auto upgrade = std::make_shared<UpgradeButton>(
            *UP_POINTS_PER_CLICK(), key);

        upgrade->SetParent(root);
        upgrade->Margin({32 + index * gap, 0, 32, 32});
        upgrade->DefineLayout({xl::Layout::HorizontalLeft, xl::Layout::VerticalTop});

        WithObject(upgrade);
    }

    auto toMainScene = std::make_shared<SceneSwitchButton>(*SPR_MAIN_SCENE_BUTTON(), MAIN_SCENE);
    toMainScene->SetParent(root);
    toMainScene->DefineLayout({xl::Layout::HorizontalRight, xl::Layout::VerticalTop});
    toMainScene->Margin({32, 32});

    RegisterEvent(xl::xlEngine::GetBus().subscribe<SceneSwitchRequest>(
        [renderer](const SceneSwitchRequest &signal)
        {
            Scenes::SwitchScene(renderer, signal.m_scene);
        }));

    WithObject(root);
    WithObject(toMainScene);
}
std::unique_ptr<xl::IGameScene> ShopScene::clone() const
{
    return std::make_unique<ShopScene>(*this);
}