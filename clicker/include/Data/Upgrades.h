#include <utility>

//
// Created by XL1TTE on 11.12.2025.
//

#ifndef CLICKER_UPGRADES_H
#define CLICKER_UPGRADES_H

struct Upgrade
{
    explicit Upgrade(std::string id,
                     const int   level       = 0,
                     const int   maxLevel    = 99,
                     const int   perLvlFlat  = 1,
                     const float perLvlMulti = 2.f)
        : m_id(std::move(id)),
          m_level(level),
          m_maxLevel(maxLevel),
          m_PerLvlFlat(perLvlFlat),
          m_PerLvlMultiplier(perLvlMulti)
    {
    }
    std::string m_id;
    int         m_level;
    int         m_maxLevel;
    int         m_PerLvlFlat;
    float       m_PerLvlMultiplier;
};

#endif // CLICKER_UPGRADES_H
