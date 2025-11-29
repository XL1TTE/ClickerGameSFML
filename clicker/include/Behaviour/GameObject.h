//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_GAMEOBJECT_H
#define CLICKER_GAMEOBJECT_H

#include <memory>
#include <vector>

namespace sf
{
class Transform;

template <typename T>
class Vector2;
} // namespace sf
namespace sf
{
class Transformable;
}

class IBehaviourObject;

namespace sf
{
class RenderTarget;
}

class GameObject
{
  public:
    GameObject()          = default;
    virtual ~GameObject() = default;

  protected:
    std::vector<std::weak_ptr<IBehaviourObject>> m_behaviours;
    std::weak_ptr<GameObject>                    m_parent;
    std::vector<std::weak_ptr<GameObject>>       m_childrens;

  public:
    virtual void Awake();
    virtual void Update();
    virtual void Destroy();
    virtual void Draw(const std::weak_ptr<sf::RenderTarget> &);

    virtual class sf::Vector2<float> getSize();
    virtual sf::Vector2<float>       getPosition();
    virtual sf::Transform            getTransform();

    void SetParent(const std::weak_ptr<GameObject> &parent);
};

#endif // CLICKER_GAMEOBJECT_H
