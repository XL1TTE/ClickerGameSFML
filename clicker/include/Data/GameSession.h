//
// Created by XL1TTE on 09.12.2025.
//

#ifndef CLICKER_GAMESESSION_H
#define CLICKER_GAMESESSION_H
#include "SignalBus/SignalBus.h"
#include "Signals/Signals.h"
#include "xlEngine.h"

#include <algorithm>
#include <cstdint>

struct GameSession
{
  private:
    float m_healthPercent = 1;
    int   m_maxHealth     = 10;
    int   m_playerHealth  = 10;

    std::uint32_t m_gold = 0;

  public:
    [[nodiscard]] std::uint32_t GetGold() const;
    [[nodiscard]] float         GetHealthPercent() const;
    void                        AddGold(int value);
    void                        AddHealth(int value);

    struct Stats
    {
        unsigned int GoldPerClick  = 1;
        unsigned int GoldPerSecond = 0;
    };

    Stats Stats;
};

inline std::uint32_t GameSession::GetGold() const
{
    return m_gold;
}
inline float GameSession::GetHealthPercent() const
{
    return static_cast<float>(m_playerHealth) / static_cast<float>(m_maxHealth);
}
inline void GameSession::AddGold(const int value)
{
    m_gold += value;
}
inline void GameSession::AddHealth(const int value)
{
    m_playerHealth = std::clamp(m_playerHealth + value, 0, m_maxHealth);
    xl::xlEngine::GetBus().emit(PlayerHealthChanged(m_playerHealth, GetHealthPercent()));
}

#endif // CLICKER_GAMESESSION_H
