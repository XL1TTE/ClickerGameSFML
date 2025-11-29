//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_IGAMESCENE_H
#define CLICKER_IGAMESCENE_H
#include <memory>
#include <vector>

class GameObject;

namespace sf
{
class RenderTarget;
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
    explicit IGameScene(const std::weak_ptr<sf::RenderTarget> &);

  protected:
    std::vector<std::shared_ptr<GameObject>> m_Objects;

  protected:
    void WithObject(const std::shared_ptr<GameObject> &obj);

  public:
    void Awake() const;
    void Update(const float &dt) const;
    void Draw(const std::weak_ptr<sf::RenderTarget> &) const;
};

#endif // CLICKER_IGAMESCENE_H
