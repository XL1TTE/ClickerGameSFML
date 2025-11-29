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

  public:
    std::shared_ptr<sf::RenderWindow> m_windowPtr;

  private:
    void        UpdateWindow() noexcept;
    static bool IsInitialized() noexcept;

  public:
    static Game &Init() noexcept;
    static void  Update();

    static void SetFrameRate(uint8_t limit) noexcept;
};

#endif // CLICKER_GAME_H
