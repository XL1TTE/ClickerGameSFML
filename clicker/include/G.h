//
// Created by XL1TTE on 30.11.2025.
//

#ifndef CLICKER_G_H
#define CLICKER_G_H
#include <cstdint>

class G
{
  private:
    static std::uint32_t m_gold;

  public:
    static std::uint32_t GetGold();
    static void          AddGold(const uint32_t amount);
    static void          RemoveGold(const uint32_t amount);
};

#endif // CLICKER_G_H
