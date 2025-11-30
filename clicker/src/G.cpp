//
// Created by XL1TTE on 30.11.2025.
//

#include "G.h"
#include <algorithm>
#include <iostream>

std::uint32_t G::m_gold = 0;

std::uint32_t G::GetGold()
{
    return m_gold;
}
void G::AddGold(const uint32_t amount)
{
    std::cout << "Added gold: " << amount << "\n";
    G::m_gold += amount;
}
void G::RemoveGold(const uint32_t amount)
{
    G::m_gold = std::ranges::min(G::m_gold - amount, static_cast<unsigned int>(0));
}