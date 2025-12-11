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
    int   m_maxHealth     = 10;
    int   m_playerHealth  = 10;

    float m_gold = 0;

  public:
    [[nodiscard]] float GetGold() const;
    [[nodiscard]] float GetHealthPercent() const;
    void                AddGold(float value);
    void                AddHealth(int value);

    struct IStat
    {
        virtual ~IStat() = default;

        int m_level    = 1;
        int m_maxLevel = 99;
        int m_cost     = 100;

        [[nodiscard]] virtual double value() const = 0;
        virtual void                 levelUp()
        {
            if (m_level + 1 > m_maxLevel)
            {
                return;
            }
            ++m_level;
        }
        virtual bool isLevelCaped()
        {
            return m_level >= m_maxLevel;
        }
        virtual int getCost()
        {
            return m_cost;
        }
    };

    struct GoldPerClick final : IStat
    {
        [[nodiscard]] double value() const override
        {
            return std::pow(m_level, 2);
        }
        int getCost() override
        {
            return std::pow(m_level, 2) * m_cost;
        }
    };

    std::unordered_map<std::string, std::shared_ptr<IStat>> m_Stats = {
        {"gold_per_click", std::make_shared<GoldPerClick>()}};
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
}
inline void GameSession::AddHealth(const int value)
{
    m_playerHealth = std::clamp(m_playerHealth + value, 0, m_maxHealth);
    xl::xlEngine::GetBus().emit(PlayerHealthChanged(m_playerHealth, GetHealthPercent()));
}

#endif // CLICKER_GAMESESSION_H
