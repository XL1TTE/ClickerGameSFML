//
// Created by XL1TTE on 09.12.2025.
//

#include "GUI/Controls/MonsterSpawner.h"
#include "Monsters/BaseMonster.h"
#include "SFML/Graphics/Sprite.hpp"
#include "xlEngine.h"
MonsterSpawner::MonsterSpawner(const std::weak_ptr<GameObject> &spawnIn, const float cooldown, const BaseMonster &monster)
    : m_timeLeft(cooldown),
      m_cooldown(cooldown),
      m_monsterPrototype(std::make_unique<BaseMonster>(monster)),
      m_spawnIn(spawnIn)
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
        m_timeLeft = m_cooldown;
    }
    m_timeLeft -= dt;
}