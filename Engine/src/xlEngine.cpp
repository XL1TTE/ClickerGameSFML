//
// Created by XL1TTE on 29.11.2025.
//

#include "../include/xlEngine.h"

#include "../../out/Release/_deps/sfml-src/extlibs/headers/vulkan/vulkan_core.h"
#include "EventSystems/MouseEventsSystem.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <XL_ENGINE_H>

using namespace xl;

std::unique_ptr<xlEngine> xlEngine::m_instance = nullptr;

xlEngine::xlEngine() noexcept
    : m_signalBus(std::make_shared<SignalBus>()),
      m_windowPtr(std::make_shared<sf::RenderWindow>(
          sf::VideoMode({640u, 800u}),
          "Clicker",
          sf::Style::Titlebar | sf::Style::Close))
{
}

void xlEngine::UpdateScreen() noexcept
{
    if (!IsExist())
    {
        return;
    }

    const auto window = m_instance->m_windowPtr;

    window->clear();

    if (m_instance->m_currentScene != nullptr)
    {
        m_instance->m_currentScene->Draw(window);
    }

    window->display();
}

bool xlEngine::IsExist() noexcept
{
    return m_instance != nullptr;
}

xlEngine &xlEngine::New() noexcept
{
    if (IsExist() == false)
    {
        m_instance = std::make_unique<xlEngine>();
    }
    return *m_instance;
}
xl::SignalBus &xlEngine::GetBus() noexcept
{
    if (m_instance->m_signalBus == nullptr)
    {
        m_instance->m_signalBus = std::make_shared<xl::SignalBus>();
        return *m_instance->m_signalBus;
    }
    return *m_instance->m_signalBus;
}

void xlEngine::Update()
{
    if (IsExist() == false)
    {
        return;
    }

    if (m_instance->m_clock == nullptr)
    {
        m_instance->m_clock = std::make_unique<sf::Clock>(sf::Clock());
    }

    // Delta time calculations -->
    const auto &game  = m_instance;
    game->m_deltaTime = static_cast<float>(game->m_clock->restart().asMilliseconds()) / 1000;
    // <-- Delta time calculation

    // Awake loop -->
    if (game->m_currentScene != nullptr && game->m_currentScene->m_IsInitialized == false)
    {
        game->m_currentScene->Awake();
        game->m_currentScene->m_IsInitialized = true;
    }
    // <-- Awake loop

    // Game loop -->
    if (game->m_currentScene != nullptr)
    {
        game->m_currentScene->Update(game->m_deltaTime);
        EventsUpdate();
    }
    // <-- Game loop
}
void xlEngine::EventsUpdate() noexcept
{
    if (IsExist() == false)
    {
        return;
    }
    const auto &window = m_instance->m_windowPtr;

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
                xlEngine::Exit();
            }
            if (auto evt = event.value().getIf<sf::Event::MouseMoved>())
            {
                MouseEventsSystem::ProcessPointerEvents(*m_instance->m_windowPtr, *m_instance->m_currentScene);
            }
            if (const auto evt = event.value().getIf<sf::Event::MouseButtonPressed>())
            {
                MouseEventsSystem::ProcessClickEvent(*evt, *m_instance->m_windowPtr, *m_instance->m_currentScene);
            }
        }
    }
}

std::weak_ptr<sf::RenderWindow> xlEngine::GetWindow()
{
    if (IsExist() == false)
    {
        throw std::runtime_error("Create Game via Game::New first.");
    }
    return m_instance->m_windowPtr;
}
void xlEngine::SpawnObject(const std::shared_ptr<GameObject> &obj)
{
    if (IsExist() == false)
    {
        return;
    }
    m_instance->m_currentScene->WithObject(obj);
}
void xlEngine::DestroyObject(const std::shared_ptr<GameObject> &obj)
{
    if (IsExist() == false)
    {
        return;
    }
    auto &objects = m_instance->m_currentScene->m_Objects;

    if (const auto it = std::ranges::find(objects.begin(), objects.end(), obj); it != objects.end())
    {
        (*it)->OnDestroy();

        objects.erase(it);
    }
}

void xlEngine::SetScene(std::unique_ptr<IGameScene> scene)
{
    if (IsExist() == false)
    {
        return;
    }

    DestroyScene();
    m_instance->m_currentScene = std::move(scene);
}

void xlEngine::DestroyScene()
{
    if (IsExist() == false)
    {
        return;
    }

    if (const auto &game = m_instance; game->m_currentScene != nullptr)
    {
        game->m_currentScene->Destroy();
        game->m_currentScene->m_IsInitialized = false;
    }
}

void xlEngine::SetFrameRate(const uint8_t limit) noexcept
{
    if (IsExist() == false)
    {
        return;
    }
    m_instance->m_windowPtr->setFramerateLimit(limit);
}
void xlEngine::Exit() noexcept
{
    m_instance = nullptr;
}