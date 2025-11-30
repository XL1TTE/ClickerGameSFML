//
// Created by XL1TTE on 30.11.2025.
//

#ifndef CLICKER_SIGNALBUS_H
#define CLICKER_SIGNALBUS_H
#include <functional>
#include <memory>
#include <vector>

class ISignal;

class SignalBus final
{
  private:
    struct BaseHandler
    {
        virtual ~BaseHandler() = default;
    };

    template <typename SignalType>
    struct Handler final : BaseHandler
    {
        explicit Handler(std::function<void(const SignalType &)> callback);

        std::function<void(const SignalType &)> m_callback;
    };

  public:
    SignalBus()                             = default;
    SignalBus(const SignalBus &)            = delete;
    SignalBus &operator=(const SignalBus &) = delete;

  private:
    std::unique_ptr<SignalBus>                                                 m_instance;
    std::unordered_map<std::size_t, std::vector<std::unique_ptr<BaseHandler>>> m_handlers;

  public:
    SignalBus &create();
    SignalBus &get() const;

    template <typename SignalType>
    void subscribe(std::function<void(const SignalType &)> handler);
    template <typename SignalType>
    void unsubscribe(std::function<void(const SignalType &)> handler);
    template <typename SignalType>
    void publish(const SignalType &signal);
};

#endif // CLICKER_SIGNALBUS_H
