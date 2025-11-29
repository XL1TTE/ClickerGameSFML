//
// Created by XL1TTE on 29.11.2025.
//

#include "../include/Game.h"

#include "GUI/Scenes/IGameScene.h"
#include "SFML/Graphics/RenderWindow.hpp"

std::unique_ptr<Game> Game::m_instance = nullptr;

Game::Game() noexcept
    : m_windowPtr(std::make_shared<sf::RenderWindow>(
          sf::VideoMode({640u, 800u}),
          "Clicker",
          sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize))
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

    if (const auto scene = m_instance->m_currentScene.lock())
    {
        scene->Draw(window);
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

void Game::Update()
{
    if (IsExist() == false)
    {
        return;
    }
}
std::weak_ptr<sf::RenderWindow> Game::GetWindow()
{
    return m_instance->m_windowPtr;
}

void Game::SetScene(const std::weak_ptr<IGameScene> &scene)
{
    if (IsExist() == false)
    {
        return;
    }
    m_instance->m_currentScene = scene;
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