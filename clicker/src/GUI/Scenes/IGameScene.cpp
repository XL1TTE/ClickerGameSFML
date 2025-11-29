//
// Created by XL1TTE on 29.11.2025.
//

#include "../../../include/GUI/Scenes/IGameScene.h"

#include "SFML/Graphics/RenderWindow.hpp"

IGameScene::IGameScene(const std::weak_ptr<sf::RenderWindow> &renderer) noexcept
{
    m_windowPtr = renderer;
}
void IGameScene::Clear()
{
    if (auto renderer = m_windowPtr.lock())
    {
        renderer.get()->clear(sf::Color::Black);
    }
}
void IGameScene::Render()
{
}
void IGameScene::Rerender()
{
    Clear();
    Render();
}