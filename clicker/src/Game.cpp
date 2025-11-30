//
// Created by XL1TTE on 29.11.2025.
//

#include "../include/Game.h"

#include "GUI/Scenes/IGameScene.h"
#include "SFML/Graphics/RenderWindow.hpp"

std::unique_ptr<Game> Game::m_instance = nullptr;

Game::Game() noexcept
    : m_signalBus(std::make_shared<SignalBus>()),
      m_windowPtr(std::make_shared<sf::RenderWindow>(
          sf::VideoMode({640u, 800u}),
          "Clicker",
          sf::Style::Titlebar | sf::Style::Close))
{
}

void Game::UpdateScreen() noexcept
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

bool Game::IsExist() noexcept
{
    return m_instance != nullptr;
}

Game &Game::New() noexcept
{
    if (IsExist() == false)
    {
        m_instance = std::make_unique<Game>();
    }
    return *m_instance;
}
SignalBus &Game::GetBus() noexcept
{
    if (m_instance->m_signalBus == nullptr)
    {
        m_instance->m_signalBus = std::make_shared<SignalBus>();
        return *m_instance->m_signalBus;
    }
    return *m_instance->m_signalBus;
}

void Game::Update()
{
    if (IsExist() == false)
    {
        return;
    }
}
std::weak_ptr<sf::RenderWindow> Game::GetWindow()
{
    if (IsExist() == false)
    {
        throw std::runtime_error("Create Game via Game::New first.");
    }
    return m_instance->m_windowPtr;
}

void Game::SetScene(std::unique_ptr<IGameScene> scene)
{
    if (IsExist() == false)
    {
        return;
    }

    DestroyScene();
    m_instance->m_currentScene = std::move(scene);
}
void Game::DestroyScene()
{
    if (IsExist() == false)
    {
        return;
    }
    if (m_instance->m_currentScene != nullptr)
    {
        m_instance->m_currentScene->Destroy();
    }
}
void Game::SetFrameRate(const uint8_t limit) noexcept
{
    if (IsExist() == false)
    {
        return;
    }
    m_instance->m_windowPtr->setFramerateLimit(limit);
}
void Game::Exit() noexcept
{
    m_instance = nullptr;
}