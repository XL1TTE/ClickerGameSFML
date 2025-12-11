//
// Created by XL1TTE on 09.12.2025.
//

#include "GUI/Controls/MonsterSpawner.h"
#include "Monsters/BaseMonster.h"
#include "SFML/Graphics/Sprite.hpp"
#include "xlEngine.h"
MonsterSpawner::MonsterSpawner(const std::weak_ptr<GameObject> &spawnIn, const float cooldown, const BaseMonster &monster)
    : m_monsterPrototype(std::make_unique<BaseMonster>(monster)),
      m_spawnIn(spawnIn),
      m_timeLeft(cooldown),
      m_cooldown(cooldown), m_min_cooldown(cooldown), m_max_cooldown(cooldown)
{
}
MonsterSpawner::MonsterSpawner(const std::weak_ptr<GameObject> &spawnIn,
                               float                            min_cooldown,
                               float                            max_cooldown,
                               const BaseMonster               &monster)
    : m_monsterPrototype(std::make_unique<BaseMonster>(monster)),
      m_spawnIn(spawnIn),
      m_timeLeft(xl::xlEngine::Math::RandFloat(min_cooldown, max_cooldown)),
      m_cooldown(xl::xlEngine::Math::RandFloat(min_cooldown, max_cooldown)),
      m_min_cooldown(min_cooldown),
      m_max_cooldown(max_cooldown)
{
}

void MonsterSpawner::Spawn()
{
    m_monster = std::make_shared<BaseMonster>(*m_monsterPrototype);
    m_monster->DefineLayout({xl::Layout::HorizontalCenter,
                             xl::Layout::VerticalCenter});
    m_monster->SetParent(m_spawnIn);
    xl::xlEngine::SpawnObject(m_monster);
}
void MonsterSpawner::UpdateCooldown()
{
    m_cooldown = xl::xlEngine::Math::RandFloat(m_min_cooldown, m_max_cooldown);
    std::cout << "New monster spawn cooldown: " << m_cooldown << "\n";
}
void MonsterSpawner::Update(const float dt)
{
    if (m_monster != nullptr && !m_monster->isDied)
    {
        return;
    }
    m_monster.reset();

    if (m_timeLeft <= 0)
    {
        Spawn();
        UpdateCooldown();
        m_timeLeft = m_cooldown;
    }
    m_timeLeft -= dt;
}
sf::Vector2<float> MonsterSpawner::GetSize() const
{
    return {0, 0};
}
void MonsterSpawner::Draw(const std::weak_ptr<sf::RenderTarget> &)
{
}