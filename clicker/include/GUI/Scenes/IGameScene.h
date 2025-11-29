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
    IGameScene()                       = default;
    IGameScene(IGameScene &)           = delete;
    IGameScene(IGameScene &&) noexcept = default;

    IGameScene &operator=(IGameScene &)           = delete;
    IGameScene &operator=(IGameScene &&) noexcept = default;

    virtual ~IGameScene() = default;

  protected:
    std::weak_ptr<sf::RenderWindow> m_windowPtr;

  public:
    virtual void Render(const std::weak_ptr<sf::RenderWindow> &);
};

#endif // CLICKER_IGAMESCENE_H
