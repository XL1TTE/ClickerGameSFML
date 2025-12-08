//
// Created by XL1TTE on 29.11.2025.
//

#ifndef XLENGINE_GAMEOBJECT_H
#define XLENGINE_GAMEOBJECT_H

#include <memory>
#include <vector>

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
    std::vector<std::weak_ptr<IBehaviourObject>> m_behaviours;
    std::weak_ptr<GameObject>                    m_parent;

  public:
    virtual void Awake();
    virtual void Update(const int32_t &dt);
    virtual void Destroy();
    virtual void Draw(const std::weak_ptr<sf::RenderTarget> &);

    [[nodiscard]] virtual sf::Vector2<float> GetSize() const;
    [[nodiscard]] virtual sf::Vector2<float> GetPosition() const;
    [[nodiscard]] virtual sf::Transform      GetTransform() const;

    void SetParent(const std::weak_ptr<GameObject> &parent);
};

} // namespace xl
#endif // XLENGINE_GAMEOBJECT_H