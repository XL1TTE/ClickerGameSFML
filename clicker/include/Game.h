//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_GAME_H
#define CLICKER_GAME_H
#include "SFML/System/Clock.hpp"

#include <memory>
namespace xl
{
class SignalBus;
class IGameScene;
} // namespace xl
namespace sf
{
class RenderWindow;
}

class Game final
{
  public:
    Game() noexcept;

    Game(const Game &)            = delete;
    Game &operator=(const Game &) = delete;
    Game(Game &&)                 = delete;
    Game &operator=(Game &&)      = delete;

  public:
    ~Game() = default;

  private:
    static std::unique_ptr<Game> m_instance;

    sf::Clock                       m_clock     = sf::Clock();
    int32_t                         m_deltaTime = 0.0f;
    std::unique_ptr<xl::IGameScene> m_currentScene;
    std::shared_ptr<xl::SignalBus>  m_signalBus;

  public:
    std::shared_ptr<sf::RenderWindow> m_windowPtr;

  public:
    static Game          &New() noexcept;
    static xl::SignalBus &GetBus() noexcept;

    /**
     * \brief Game's update loop.
     * \return False if game was closed.
     */
    static void                            Update();
    static void                            UpdateScreen() noexcept;
    static std::weak_ptr<sf::RenderWindow> GetWindow();
    static void                            SetScene(std::unique_ptr<xl::IGameScene> scene);
    static void                            DestroyScene();
    static void                            SetFrameRate(uint8_t limit) noexcept;
    static bool                            IsExist() noexcept;
    static void                            Exit() noexcept;
};

#endif // CLICKER_GAME_H
