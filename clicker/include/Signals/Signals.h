//
// Created by XL1TTE on 30.11.2025.
//

#ifndef CLICKER_GOLDCHANGEDSIGNAL_H
#define CLICKER_GOLDCHANGEDSIGNAL_H
#include "SignalBus/Signals/ISignal.h"

class GoldChangedSignal : public xl::ISignal
{
  public:
    explicit GoldChangedSignal(const unsigned int value)
    {
        m_value = value;
    }

  public:
    unsigned int m_value;
};

class MonsterAttackedSignal : public xl::ISignal
{
  public:
    explicit MonsterAttackedSignal(const int damage)
    {
        m_damage = damage;
    }

  public:
    unsigned int m_damage;
};

#endif // CLICKER_GOLDCHANGEDSIGNAL_H
