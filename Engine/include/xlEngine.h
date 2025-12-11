//
// Created by XL1TTE on 29.11.2025.
//

#ifndef XLENGINE_ENGINE_H
#define XLENGINE_ENGINE_H
#include "SFML/System/Clock.hpp"
#include <memory>
#include <random>

namespace xl
{
class GameObject;
}
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
    xlEngine(const xlEngine &)            = delete;
    xlEngine &operator=(const xlEngine &) = delete;
    xlEngine(xlEngine &&)                 = delete;
    xlEngine &operator=(xlEngine &&)      = delete;

  private:
    xlEngine() noexcept;
    ~xlEngine() = default;

    bool                        isExited = false;
    std::unique_ptr<sf::Clock>  m_clock;
    float                       m_deltaTime = 0.0f;
    std::unique_ptr<IGameScene> m_currentScene;

  public:
    std::shared_ptr<sf::RenderWindow> m_windowPtr;

    static xlEngine  &Get() noexcept;
    static SignalBus &GetBus() noexcept;

    /**
     * \brief Game's update loop.
     * \return False if game was closed.
     */
    static void                            Update();
    static void                            EventsUpdate() noexcept;
    static void                            UpdateScreen() noexcept;
    static std::weak_ptr<sf::RenderWindow> GetWindow();
    static void                            SpawnObject(const std::shared_ptr<GameObject> &obj);
    static void                            DestroyObject(const std::shared_ptr<GameObject> &obj);
    static void                            SetScene(std::unique_ptr<IGameScene> scene);
    static void                            DestroyScene();
    static void                            SetFrameRate(uint8_t limit) noexcept;
    static bool                            IsExited() noexcept;
    static void                            Exit() noexcept;

  public:
    class Math
    {
      public:
        static float RandFloat(float min, float max)
        {
            std::random_device rd;
            std::mt19937       eng(rd.entropy() ? rd() : std::chrono::steady_clock::now().time_since_epoch().count());

            std::uniform_real_distribution distr(min, max);
            return distr(eng);
        }
    };
};
} // namespace xl
#endif // XLENGINE_ENGINE_H
