//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_GAME_H
#define CLICKER_GAME_H
#include <memory>

namespace sf
{
class RenderWindow;
}

class IGameScene;

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

    std::weak_ptr<IGameScene> m_currentScene;

  public:
    std::shared_ptr<sf::RenderWindow> m_windowPtr;

  public:
    static Game &New() noexcept;

    /**
     * \brief Game's update loop.
     * \return False if game was closed.
     */
    static void                            Update();
    static void                            UpdateScreen() noexcept;
    static std::weak_ptr<sf::RenderWindow> GetWindow();
    static void                            SetScene(const std::weak_ptr<IGameScene> &scene);
    static void                            SetFrameRate(uint8_t limit) noexcept;
    static bool                            IsExist() noexcept;
    static void                            Exit() noexcept;
};

#endif // CLICKER_GAME_H
