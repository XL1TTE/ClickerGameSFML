//
// Created by XL1TTE on 29.11.2025.
//

#include "Scenes/IGameScene.h"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace xl;

IGameScene::~IGameScene()
{
    Destroy();
}
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
        // m_Objects.push_back(obj);
        m_PendingObjectsToAdd.push_back(obj);
    }
}
void IGameScene::ProcessPendingObjects()
{
    std::vector<std::shared_ptr<GameObject>> objects_to_process;
    objects_to_process.swap(m_PendingObjectsToAdd);
    for (const auto &obj : objects_to_process)
    {
        m_Objects.push_back(obj);
        obj->Awake();
    }
}

void IGameScene::Awake()
{
    for (const auto &obj : m_Objects)
    {
        obj->Awake();
    }
    std::cout << "OnAwake" << std::endl;
    OnAwake();
}
void IGameScene::OnAwake()
{
}
void IGameScene::OnEnable()
{
}
void IGameScene::OnDisable()
{
}
void IGameScene::OnUpdate(float dt)
{
}
void IGameScene::Update(const float dt)
{
    for (const auto &obj : m_Objects)
    {
        obj->Update(dt);
    }

    ProcessPendingObjects();
    OnUpdate(dt);
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
        obj->OnDestroy();
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
