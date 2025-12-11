//
// Created by XL1TTE on 30.11.2025.
//

#ifndef CLICKER_GOLDCHANGEDSIGNAL_H
#define CLICKER_GOLDCHANGEDSIGNAL_H
#include "Scenes/Scenes.h"
#include "SignalBus/Signals/ISignal.h"

class GoldChangedSignal : public xl::ISignal
{
  public:
    explicit GoldChangedSignal(const unsigned int value)
        : m_value(value)
    {
    }

    unsigned int m_value;
};

class MonsterAttackedSignal : public xl::ISignal
{
  public:
    explicit MonsterAttackedSignal(const int damage)
        : m_damage(damage)
    {
    }

    int m_damage;
};
class PlayerHealthChanged : public xl::ISignal
{
  public:
    explicit PlayerHealthChanged(const int health, float healthPercent)
        : m_health(health), m_healthPercent(healthPercent)
    {
    }

    int   m_health;
    float m_healthPercent;
};

class SceneSwitchRequest : public xl::ISignal
{

  public:
    explicit SceneSwitchRequest(const SceneName &scene)
        : m_scene(scene)
    {
    }

    SceneName m_scene;
};

#endif // CLICKER_GOLDCHANGEDSIGNAL_H
