//
// Created by XL1TTE on 30.11.2025.
//

#ifndef CLICKER_SIGNALBUS_H
#define CLICKER_SIGNALBUS_H
#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <typeindex>

namespace xl
{

// Define a token type for safe unsubscribing
using SubscriptionToken = unsigned int;

// --- Level 1: Non-templated Base Interface (Type Erasure) ---
// This is what we store in our map.
class IDelegate
{
  public:
    virtual ~IDelegate() = default;
    // We cannot call 'invoke' or 'broadcast' here because we don't know the parameters yet.
    // The concrete SignalBus implementation will handle casting back to the correct type.
};

// --- Level 2: Templated Concrete Delegate ---
// Manages actual subscription/unsubscription for a specific signal type.
template <typename Param>
class Delegate final : public IDelegate
{
  public:
    using HandlerFunction = std::function<void(const Param &)>;

    SubscriptionToken add(const HandlerFunction &handler)
    {
        SubscriptionToken token = m_nextToken++;
        m_handlers[token]       = handler;
        return token;
    }

    void remove(const SubscriptionToken &token)
    {
        if (m_handlers.contains(token))
        {
            m_handlers.erase(token);
        }
    }

    [[nodiscard]] std::size_t size() const
    {
        return m_handlers.size();
    }

    void invoke(const Param &param)
    {
        for (const auto &pair : m_handlers)
        {
            pair.second(param);
        }
    }

  private:
    // Stores handlers in a simple vector
    std::unordered_map<SubscriptionToken, HandlerFunction> m_handlers;
    std::atomic<SubscriptionToken>                         m_nextToken{1};
};

// --- Level 3: The SignalBus Class ---
class SignalBus final
{
  public:
    struct IConnection
    {
      protected:
        virtual ~IConnection() = default;
    };

    template <typename SignalType>
    struct Connection final : public IConnection
    {
        Connection()                              = delete;
        Connection(Connection &)                  = delete;
        Connection &operator=(const Connection &) = delete;

      public:
        Connection(const SubscriptionToken id, Delegate<SignalType> *delegatePtr)
            : m_token(id),
              m_delegatePtr(delegatePtr)
        {
            if (m_delegatePtr == nullptr)
            {
                throw std::runtime_error("Cannot create connection with null delegate pointer.");
            }
        }
        ~Connection() override
        {
            std::cout << "Connection destroyed" << "\n";
            if (m_delegatePtr != nullptr)
            {
                m_delegatePtr->remove(m_token);
            }
        }

      private:
        SubscriptionToken     m_token;
        Delegate<SignalType> *m_delegatePtr;
    };

  private:
    // We use std::type_index (or a custom hash of the type name) as the key.
    std::unordered_map<std::type_index, std::unique_ptr<IDelegate>> m_registrar;

    // Helper to get or create the specific Delegate<T> instance
    template <typename SignalType>
    Delegate<SignalType> &getOrCreateDelegate()
    {
        const std::type_index key = typeid(SignalType);

        if (!m_registrar.contains(key))
        {
            // If not found, create a new concrete Delegate<SignalType>
            m_registrar[key] = std::make_unique<Delegate<SignalType>>();
        }

        auto ptr = dynamic_cast<Delegate<SignalType> *>(m_registrar[key].get());
        if (!ptr)
        {
            throw std::runtime_error("SignalBus internal error: Type cast failed.");
        }
        return *ptr;
    }

  public:
    template <typename SignalType>
    std::shared_ptr<Connection<SignalType>> subscribe(const std::function<void(const SignalType &)> &handler)
    {
        // Use the helper to get the correct, type-safe delegate instance
        Delegate<SignalType> &delegate = getOrCreateDelegate<SignalType>();
        const auto           &token    = delegate.add(handler);

        // Pass the token by value (copy) and delegate as a pointer
        return std::make_shared<Connection<SignalType>>(token, &delegate);
    }

    template <typename SignalType>
    void unsubscribe(const SubscriptionToken &token)
    {
        Delegate<SignalType> &delegate = getOrCreateDelegate<SignalType>();
        delegate.remove(token);
    }

    template <typename SignalType>
    void emit(const SignalType &signal)
    {
        const std::type_index key = typeid(SignalType);

        if (m_registrar.contains(key))
        {
            // Get the IDelegate pointer, cast it back to the concrete type
            auto &delegateInstance = static_cast<Delegate<SignalType> &>(*m_registrar[key]);
            delegateInstance.invoke(signal);
        }
        else
        {
        }
    }

  public:
    SignalBus()                             = default;
    SignalBus(const SignalBus &)            = delete;
    SignalBus &operator=(const SignalBus &) = delete;

  private:
    static std::unique_ptr<SignalBus>                               m_instance;
    std::unordered_map<std::type_index, std::unique_ptr<IDelegate>> m_registar;

  public:
    static SignalBus &create();
    static SignalBus &get();
};

} // namespace xl
#endif // CLICKER_SIGNALBUS_H