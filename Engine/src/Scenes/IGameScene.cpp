//
// Created by XL1TTE on 29.11.2025.
//

#include "Scenes/IGameScene.h"
#include "Behaviour/GameObject.h"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace xl;

IGameScene::IGameScene(const std::weak_ptr<sf::RenderTarget> &)
{
}
void IGameScene::RegisterEvent(const std::shared_ptr<SignalBus::IConnection> &connection)
{
    if (connection != nullptr)
    {
        m_Events.push_back(connection);
    }
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
void IGameScene::Update(const int32_t &dt) const
{
    for (const auto &obj : m_Objects)
    {
        obj->Update(dt);
    }
}
void IGameScene::Draw(const std::weak_ptr<sf::RenderTarget> &drawer) const
{
    for (const auto &obj : m_Objects)
    {
        obj->Draw(drawer);
    }
}
void IGameScene::Destroy()
{
    for (const auto &obj : m_Objects)
    {
        obj->Destroy();
    }

    m_Objects.clear();
    for (auto &evt : m_Events)
    {
        if (evt != nullptr)
        {
            evt.reset();
        }
    }
    m_Events.clear();
}
