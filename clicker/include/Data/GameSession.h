//
// Created by XL1TTE on 09.12.2025.
//

#ifndef CLICKER_GAMESESSION_H
#define CLICKER_GAMESESSION_H
#include "SignalBus/SignalBus.h"
#include "Signals/Signals.h"
#include "Upgrades.h"
#include "xlEngine.h"

#include <algorithm>
#include <cstdint>

struct GameSession
{
  private:
    float m_healthPercent = 1;
    int   m_maxHealth     = 100;
    int   m_playerHealth  = 100;

    float m_gold = 0;

  public:
    [[nodiscard]] float GetGold() const;
    [[nodiscard]] float GetHealthPercent() const;
    void                AddGold(float value);
    void                AddHealth(int value);

    struct IStat
    {
        IStat(int level = 0, int maxLevel = 99, float cost = 10.0f)
            : m_level(level), m_maxLevel(maxLevel), m_cost(cost)
        {
        }
        virtual ~IStat() = default;

        int   m_level;
        int   m_maxLevel;
        float m_cost;

        [[nodiscard]] virtual double value() const = 0;
        virtual void                 levelUp()
        {
            if (m_level + 1 > m_maxLevel)
            {
                return;
            }
            m_level += 1;
        }
        virtual bool isLevelCaped()
        {
            return m_level >= m_maxLevel;
        }
        virtual float getCost()
        {
            return m_cost;
        }
    };

    struct GoldPerClick final : IStat
    {
        GoldPerClick()
            : IStat(1, 99, 10.f)
        {
        }
        [[nodiscard]] double value() const override
        {
            return std::pow(m_level, 2);
        }
        float getCost() override
        {
            return m_cost * static_cast<float>(std::pow(m_level + 1, 2));
        }
    };
    struct StrongGoldPerClick final : IStat
    {
        StrongGoldPerClick()
            : IStat(0, 10, 100.f)
        {
        }
        [[nodiscard]] double value() const override
        {
            if (m_level < 1)
            {
                return 0;
            }
            return std::pow(m_level + 1, 3);
        }
        float getCost() override
        {
            if (m_level < 1)
            {
                return 400.f;
            }
            return std::pow(m_level + 1, 3) * m_cost;
        }
    };
    struct GoldPerSecond final : IStat
    {
        GoldPerSecond()
            : IStat(0, 99, 50.f)
        {
        }
        [[nodiscard]] double value() const override
        {
            return std::pow(m_level, 2);
        }
        float getCost() override
        {
            return m_cost * static_cast<float>(std::pow(m_level + 1, 2));
        }
    };

    std::unordered_map<std::string, std::shared_ptr<IStat>> m_Stats = {
        {"gold_per_click", std::make_shared<GoldPerClick>()},
        {"strong_gold_per_click", std::make_shared<StrongGoldPerClick>()},
        {"gold_per_second", std::make_shared<GoldPerSecond>()},
    };
};

inline float GameSession::GetGold() const
{
    return m_gold;
}
inline float GameSession::GetHealthPercent() const
{
    return static_cast<float>(m_playerHealth) / static_cast<float>(m_maxHealth);
}
inline void GameSession::AddGold(const float value)
{
    m_gold += value;
    xl::xlEngine::GetBus().emit(GoldChangedSignal(m_gold));
}
inline void GameSession::AddHealth(const int value)
{
    m_playerHealth = std::clamp(m_playerHealth + value, 0, m_maxHealth);
    xl::xlEngine::GetBus().emit(PlayerHealthChanged(m_playerHealth, GetHealthPercent()));
}

#endif // CLICKER_GAMESESSION_H
