//
// Created by XL1TTE on 29.11.2025.
//

#ifndef XLENGINE_GAMEOBJECT_H
#define XLENGINE_GAMEOBJECT_H

#include "SignalBus/SignalBus.h"
#include "xlEngine.h"

#include <functional>
#include <memory>
#include <vector>

namespace xl
{
class ISignal;
class IGameScene;
} // namespace xl
namespace sf
{
class Transformable;
class Transform;
class RenderTarget;
template <typename T>
class Vector2;
} // namespace sf

namespace xl
{

class IBehaviourObject;

class GameObject
{

  public:
    virtual ~GameObject() = default;

  protected:
    std::vector<std::weak_ptr<IBehaviourObject>>         m_behaviours;
    std::weak_ptr<GameObject>                            m_parent;
    std::vector<std::shared_ptr<SignalBus::IConnection>> m_events;

  public:
    virtual void Awake();
    virtual void Update(float dt);
    virtual void OnDestroy();
    virtual void Draw(const std::weak_ptr<sf::RenderTarget> &) = 0;

    [[nodiscard]] virtual sf::Vector2<float> GetSize() const = 0;
    [[nodiscard]] virtual sf::Vector2<float> GetPosition() const;
    [[nodiscard]] virtual sf::Transform      GetTransform() const;

    template <typename T>
    void RegisterEvent(const std::function<void(const T &)> &handler);

    void SetParent(const std::weak_ptr<GameObject> &parent);
};
template <typename T>
void GameObject::RegisterEvent(const std::function<void(const T &)> &handler)
{
    m_events.push_back(xlEngine::GetBus().subscribe<T>(handler));
}

} // namespace xl
#endif // XLENGINE_GAMEOBJECT_H