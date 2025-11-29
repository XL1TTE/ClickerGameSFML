//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_IGAMESCENE_H
#define CLICKER_IGAMESCENE_H
#include <memory>

namespace sf
{
class RenderWindow;
}

class IGameScene
{

  public:
    IGameScene() = delete;
    explicit IGameScene(const std::weak_ptr<sf::RenderWindow> &) noexcept;

    IGameScene(IGameScene &)                    = delete;
    explicit IGameScene(IGameScene &&) noexcept = default;

    IGameScene &operator=(IGameScene &)           = delete;
    IGameScene &operator=(IGameScene &&) noexcept = default;

    virtual ~IGameScene() = default;

  protected:
    std::weak_ptr<sf::RenderWindow> m_windowPtr;

  public:
    virtual void Clear();
    virtual void Render();

    /**
     * \brief Calls both clear and render.
     */
    void Rerender();
};

#endif // CLICKER_IGAMESCENE_H
