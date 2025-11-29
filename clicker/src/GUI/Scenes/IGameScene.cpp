//
// Created by XL1TTE on 29.11.2025.
//

#include "../../../include/GUI/Scenes/IGameScene.h"

#include "Behaviour/GameObject.h"
#include "SFML/Graphics/RenderWindow.hpp"

IGameScene::IGameScene(const std::weak_ptr<sf::RenderTarget> &)
{
}
void IGameScene::WithObject(const std::shared_ptr<GameObject> &obj)
{
    if (obj)
    {
        m_Objects.push_back(obj);
    }
}
void IGameScene::Awake() const
{
    for (const auto &obj : m_Objects)
    {
        obj->Awake();
    }
}
void IGameScene::Update(const float &dt) const
{
    for (const auto &obj : m_Objects)
    {
        obj->Update();
    }
}
void IGameScene::Draw(const std::weak_ptr<sf::RenderTarget> &drawer) const
{
    for (const auto &obj : m_Objects)
    {
        obj->Draw(drawer);
    }
}
