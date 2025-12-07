//
// Created by XL1TTE on 30.11.2025.
//
#include "SignalBus/SignalBus.h"

using namespace xl;

std::unique_ptr<SignalBus> SignalBus::m_instance = nullptr;

SignalBus &SignalBus::create()
{
    m_instance = std::make_unique<SignalBus>();
    return *m_instance;
}
SignalBus &SignalBus::get()
{
    if (!m_instance)
    {
        throw std::runtime_error("SignalBus not created. Call create() first.");
    }
    return *m_instance;
}
