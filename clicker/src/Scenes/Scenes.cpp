//
// Created by XL1TTE on 30.11.2025.
//

#include "Scenes/Scenes.h"
#include "GUI/Scenes/MainScene.h"

namespace
{
std::unique_ptr<MainScene> m_mainScene = nullptr;
} // namespace
void Scenes::LoadScenes(const std::weak_ptr<sf::RenderTarget> &renderer)
{
    m_mainScene = std::make_unique<MainScene>(renderer);
}
std::unique_ptr<IGameScene> Scenes::GetMainScene()
{
    return std::move(m_mainScene);
}
std::unique_ptr<IGameScene> Scenes::CreateMainScene(const std::weak_ptr<sf::RenderTarget> &renderer)
{
    return std::make_unique<MainScene>(renderer);
}
