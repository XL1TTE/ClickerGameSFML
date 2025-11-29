//
// Created by XL1TTE on 29.11.2025.
//

#include "../include/Game.h"
#include "SFML/Graphics/RenderWindow.hpp"

std::unique_ptr<Game> Game::m_instance = nullptr;

Game::Game() noexcept
    : m_windowPtr(std::make_unique<sf::RenderWindow>(
          sf::VideoMode({640u, 800u}),
          "Clicker",
          sf::Style::Titlebar | sf::Style::Close))
{
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Game::UpdateWindow() noexcept
{
    if (!IsInitialized())
    {
        return;
    }

    const auto window = m_instance->m_windowPtr;
    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
            }
        }

        window->clear();
        window->display();
    }
}

bool Game::IsInitialized() noexcept
{
    return m_instance != nullptr;
}

Game &Game::Init() noexcept
{
    if (IsInitialized() == false)
    {
        m_instance = std::make_unique<Game>();
    }
    return *m_instance;
}

void Game::Update()
{
    if (IsInitialized() == false)
    {
        return;
    }
    m_instance->UpdateWindow();
}
void Game::SetFrameRate(uint8_t limit) noexcept
{
    if (IsInitialized() == false)
    {
        return;
    }
    m_instance->m_windowPtr->setFramerateLimit(144);
}