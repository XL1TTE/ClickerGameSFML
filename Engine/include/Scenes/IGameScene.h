//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_IGAMESCENE_H
#define CLICKER_IGAMESCENE_H
#include "Behaviour/GameObject.h"
#include "SignalBus/SignalBus.h"

#include <memory>
#include <vector>

namespace sf
{
class RenderTarget;
}

namespace xl
{

class SignalBus;
class GameObject;

class IGameScene
{
  public:
    bool m_IsInitialized = false;

    IGameScene()                       = default;
    IGameScene(const IGameScene &)     = default;
    IGameScene(IGameScene &&) noexcept = default;

    IGameScene &operator=(const IGameScene &)     = default;
    IGameScene &operator=(IGameScene &&) noexcept = default;

    virtual ~IGameScene() = default;

  protected:
    explicit IGameScene(const std::weak_ptr<sf::RenderTarget> &);

  protected:
    std::vector<std::shared_ptr<SignalBus::IConnection>> m_Events;
    std::vector<std::shared_ptr<GameObject>>             m_Objects;

  protected:
    void RegisterEvent(const std::shared_ptr<SignalBus::IConnection> &connection);
    void WithObject(const std::shared_ptr<GameObject> &obj);

  public:
    void Awake() const;
    void Update(const int32_t &dt) const;
    void Draw(const std::weak_ptr<sf::RenderTarget> &) const;
    void Destroy();

    [[nodiscard]] virtual std::unique_ptr<IGameScene> clone() const = 0;

    template <typename T>
    [[nodiscard]] std::vector<std::weak_ptr<T>> GetAllObjectsByType() const
    {
        std::vector<std::weak_ptr<T>> t_result = std::vector<std::weak_ptr<T>>();
        t_result.reserve(8);

        for (const auto &objPtr : m_Objects)
        {
            std::shared_ptr<T> sharedCastedPtr = std::dynamic_pointer_cast<T>(objPtr);

            if (sharedCastedPtr != nullptr)
            {
                std::weak_ptr<T> weakPtr(sharedCastedPtr);

                t_result.push_back(weakPtr);
            }
        }
        return t_result;
    }
};
} // namespace xl
#endif // CLICKER_IGAMESCENE_H
