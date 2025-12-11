//
// Created by XL1TTE on 30.11.2025.
//

#include "Scenes/Scenes.h"
#include "../../include/Scenes/MainScene.h"
#include "Scenes/ShopScene.h"

namespace
{
std::unique_ptr<MainScene> m_mainScene = nullptr;
} // namespace
void Scenes::LoadScenes(const std::weak_ptr<sf::RenderTarget> &renderer)
{
    m_mainScene = std::make_unique<MainScene>(renderer);
}
std::unique_ptr<xl::IGameScene> Scenes::GetMainScene()
{
    return std::move(m_mainScene);
}
std::unique_ptr<xl::IGameScene> Scenes::CreateMainScene(const std::weak_ptr<sf::RenderTarget> &renderer)
{
    return std::make_unique<MainScene>(renderer);
}
std::unique_ptr<xl::IGameScene> Scenes::CreateShopScene(const std::weak_ptr<sf::RenderTarget> &renderer)
{
    return std::make_unique<ShopScene>(renderer);
}
void Scenes::SwitchScene(const std::weak_ptr<sf::RenderTarget> &renderer, const SceneName &sceneName)
{
    switch (sceneName)
    {
    case MAIN_SCENE:
        xl::xlEngine::SetScene(CreateMainScene(renderer));
        break;
    case SHOP_SCENE:
        xl::xlEngine::SetScene(CreateShopScene(renderer));
        break;
    }
}
