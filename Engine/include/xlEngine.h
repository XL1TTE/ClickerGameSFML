//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_GAME_H
#define CLICKER_GAME_H
#include "SFML/System/Clock.hpp"
#include <memory>

namespace sf
{
class RenderWindow;
}

namespace xl
{
class SignalBus;
class IGameScene;

class xlEngine final
{
  public:
    xlEngine() noexcept;

    xlEngine(const xlEngine &)            = delete;
    xlEngine &operator=(const xlEngine &) = delete;
    xlEngine(xlEngine &&)                 = delete;
    xlEngine &operator=(xlEngine &&)      = delete;

  public:
    ~xlEngine() = default;

  private:
    static std::unique_ptr<xlEngine> m_instance;

    sf::Clock                   m_clock     = sf::Clock();
    int32_t                     m_deltaTime = 0.0f;
    std::unique_ptr<IGameScene> m_currentScene;
    std::shared_ptr<SignalBus>  m_signalBus;

  public:
    std::shared_ptr<sf::RenderWindow> m_windowPtr;

  public:
    static xlEngine  &New() noexcept;
    static SignalBus &GetBus() noexcept;

    /**
     * \brief Game's update loop.
     * \return False if game was closed.
     */
    static void                            Update();
    static void                            EventsUpdate() noexcept;
    static void                            UpdateScreen() noexcept;
    static std::weak_ptr<sf::RenderWindow> GetWindow();
    static void                            SetScene(std::unique_ptr<IGameScene> scene);
    static void                            DestroyScene();
    static void                            SetFrameRate(uint8_t limit) noexcept;
    static bool                            IsExist() noexcept;
    static void                            Exit() noexcept;
};
} // namespace xl
#endif // CLICKER_GAME_H
