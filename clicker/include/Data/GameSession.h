//
// Created by XL1TTE on 09.12.2025.
//

#ifndef CLICKER_GAMESESSION_H
#define CLICKER_GAMESESSION_H
#include <algorithm>
#include <cstdint>

struct GameSession
{
  private:
    float         m_healthPercent = 1;
    int           m_maxHealth     = 100;
    int           m_playerHealth  = 100;
    std::uint32_t m_gold          = 0;

  public:
    [[nodiscard]] std::uint32_t GetGold() const;
    void                        AddGold(const int value);
    void                        AddHealth(const int value);
};

inline std::uint32_t GameSession::GetGold() const
{
    return m_gold;
}
inline void GameSession::AddGold(const int value)
{
    m_gold += value;
}
inline void GameSession::AddHealth(const int value)
{
    m_playerHealth = std::min(0, m_playerHealth + value);
}

#endif // CLICKER_GAMESESSION_H
