//
// Created by XL1TTE on 09.12.2025.
//

#ifndef CLICKER_MONSTERSPAWNER_H
#define CLICKER_MONSTERSPAWNER_H
#include "Behaviour/GameObject.h"

class BaseMonster;
class MonsterSpawner final : public xl::GameObject
{
  public:
    explicit MonsterSpawner(const std::weak_ptr<GameObject> &spawnIn, float cooldown, const BaseMonster &monster);
    explicit MonsterSpawner(const std::weak_ptr<GameObject> &spawnIn,
                            float                            min_cooldown,
                            float                            max_cooldown,
                            const BaseMonster               &monster);

  public:
    void                             Spawn();
    void                             UpdateCooldown();
    void                             Update(float dt) override;
    [[nodiscard]] sf::Vector2<float> GetSize() const override;
    void                             Draw(const std::weak_ptr<sf::RenderTarget> &) override;

  protected:
    std::shared_ptr<BaseMonster> m_monster;
    std::unique_ptr<BaseMonster> m_monsterPrototype;
    std::weak_ptr<GameObject>    m_spawnIn;
    float                        m_timeLeft;
    float                        m_cooldown;
    const float                  m_min_cooldown;
    const float                  m_max_cooldown;
};

#endif // CLICKER_MONSTERSPAWNER_H
