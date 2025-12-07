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

#endif // CLICKER_GOLDCHANGEDSIGNAL_H
