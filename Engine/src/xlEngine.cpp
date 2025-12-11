//
// Created by XL1TTE on 29.11.2025.
//

#include "../include/xlEngine.h"

#include "../../out/Release/_deps/sfml-src/extlibs/headers/vulkan/vulkan_core.h"
#include "EventSystems/MouseEventsSystem.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <XL_ENGINE_H>

using namespace xl;

xlEngine::xlEngine() noexcept
    : m_windowPtr(std::make_shared<sf::RenderWindow>(
          sf::VideoMode({640u, 800u}),
          "Clicker",
          sf::Style::Titlebar | sf::Style::Close))
{
}

void xlEngine::UpdateScreen() noexcept
{

    const auto window = Get().m_windowPtr;

    window->clear();

    if (Get().m_currentScene != nullptr)
    {
        Get().m_currentScene->Draw(window);
    }

    window->display();
}

bool xlEngine::IsExited() noexcept
{
    return Get().isExited;
}

xlEngine &xlEngine::Get() noexcept
{
    static xlEngine instance;
    return instance;
}
xl::SignalBus &xlEngine::GetBus() noexcept
{
    return SignalBus::get();
}

void xlEngine::Update()
{

    if (Get().m_clock == nullptr)
    {
        Get().m_clock = std::make_unique<sf::Clock>(sf::Clock());
    }

    // Delta time calculations -->
    auto &game       = Get();
    game.m_deltaTime = static_cast<float>(game.m_clock->restart().asMilliseconds()) / 1000;
    // <-- Delta time calculation

    // Awake loop -->
    if (game.m_currentScene != nullptr && game.m_currentScene->m_IsInitialized == false)
    {
        game.m_currentScene->Awake();
        game.m_currentScene->m_IsInitialized = true;
    }
    // <-- Awake loop

    // Game loop -->
    if (game.m_currentScene != nullptr)
    {
        game.m_currentScene->Update(game.m_deltaTime);
        EventsUpdate();
    }
    // <-- Game loop
}
void xlEngine::EventsUpdate() noexcept
{
    const auto &window = Get().m_windowPtr;

    if (window != nullptr)
    {
        while (auto event = window->pollEvent())
        {
            if (event.has_value() == false)
            {
                continue;
            }
            if (auto evt = event.value().getIf<sf::Event::Closed>())
            {
                Exit();
            }
            if (auto evt = event.value().getIf<sf::Event::MouseMoved>())
            {
                MouseEventsSystem::ProcessPointerEvents(*Get().m_windowPtr, *Get().m_currentScene);
            }
            if (const auto evt = event.value().getIf<sf::Event::MouseButtonPressed>())
            {
                MouseEventsSystem::ProcessClickEvent(*evt, *Get().m_windowPtr, *Get().m_currentScene);
            }
        }
    }
}

std::weak_ptr<sf::RenderWindow> xlEngine::GetWindow()
{
    return Get().m_windowPtr;
}
void xlEngine::SpawnObject(const std::shared_ptr<GameObject> &obj)
{
    Get().m_currentScene->WithObject(obj);
}
void xlEngine::DestroyObject(const std::shared_ptr<GameObject> &obj)
{
    auto &objects = Get().m_currentScene->m_Objects;

    if (const auto it = std::ranges::find(objects.begin(), objects.end(), obj); it != objects.end())
    {
        (*it)->OnDestroy();

        objects.erase(it);
    }
}

void xlEngine::SetScene(std::unique_ptr<IGameScene> scene)
{
    DestroyScene();
    Get().m_currentScene = std::move(scene);
}

void xlEngine::DestroyScene()
{

    if (const auto &game = Get(); game.m_currentScene != nullptr)
    {
        game.m_currentScene->Destroy();
        game.m_currentScene->m_IsInitialized = false;
    }
}

void xlEngine::SetFrameRate(const uint8_t limit) noexcept
{
    Get().m_windowPtr->setFramerateLimit(limit);
}
void xlEngine::Exit() noexcept
{
    Get().isExited = true;
}