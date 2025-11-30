//
// Created by XL1TTE on 30.11.2025.
//
#include "SignalBus/SignalBus.h"

#include "SignalBus/Signals/ISignal.h"
#include "SignalBus/Signals/Signals.h"

#include <algorithm>
#include <typeindex>
#include <utility>

std::unique_ptr<SignalBus> SignalBus::m_instance = nullptr;

template <typename SignalType>
SignalBus::Handler<SignalType>::Handler(std::function<void(const SignalType &)> callback)
    : m_callback(std::move(callback))
{
}
template <typename SignalType>
void SignalBus::subscribe(const std::function<void(const SignalType &)> &handler)
{
    const auto type = std::type_index(typeid(SignalType));
    m_handlers[type].push_back(
        std::make_unique<Handler<SignalType>>(handler));
}
template <typename SignalType>
void SignalBus::unsubscribeAll(const std::function<void(const SignalType &)> &handler)
{
    if (const auto type = std::type_index(typeid(SignalType)); m_handlers.contains(type))
    {
        m_handlers.erase(type);
    }
}
template <typename SignalType>
void SignalBus::publish(const SignalType &signal)
{
    const auto type = std::type_index(typeid(SignalType));
    if (const auto it = m_handlers.find(type); it != m_handlers.end())
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

REGISTER_SIGNAL(ISignal);
REGISTER_SIGNAL(GoldChangedSignal);
