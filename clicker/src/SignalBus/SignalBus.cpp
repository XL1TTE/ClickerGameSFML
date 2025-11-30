//
// Created by XL1TTE on 30.11.2025.
//
#include "SignalBus/SignalBus.h"

#include "SignalBus/Signals/ISignal.h"
#include "SignalBus/Signals/Signals.h"

#include <algorithm>
#include <typeindex>

template <typename SignalType>
SignalBus::Handler<SignalType>::Handler(std::function<void(const SignalType &)> callback)
    : m_callback(callback)
{
}
template <typename SignalType>
void SignalBus::subscribe(std::function<void(const SignalType &)> handler)
{
    const auto type = std::type_index(typeid(SignalType));
    m_handlers[type.hash_code()].push_back(
        std::make_unique<Handler<SignalType>>(handler));
}
template <typename SignalType>
void SignalBus::unsubscribe(std::function<void(const SignalType &)> handler)
{
    if (const auto type = std::type_index(typeid(SignalType)); m_handlers.contains(type.hash_code()))
    {
        m_handlers.erase(type.hash_code());
    }
}
template <typename SignalType>
void SignalBus::publish(const SignalType &signal)
{
    const auto type = std::type_index(typeid(SignalType));
    if (const auto it = m_handlers.find(type.hash_code()); it != m_handlers.end())
    {
        for (auto &handler : it->second)
        {
            auto *typed_handler = dynamic_cast<SignalBus::Handler<SignalType> *>(handler.get());
            if (typed_handler && typed_handler->m_callback)
            {
                typed_handler->m_callback(signal);
            }
        }
    }
}

SignalBus &SignalBus::create()
{
    if (m_instance == nullptr)
    {
        m_instance = std::make_unique<SignalBus>();
    }
    return *m_instance;
}
SignalBus &SignalBus::get() const
{
    return *m_instance;
}

REGISTER_SIGNAL(ISignal);
REGISTER_SIGNAL(GoldChangedSignal);
