//
// Created by XL1TTE on 30.11.2025.
//

#ifndef CLICKER_SIGNALBUS_H
#define CLICKER_SIGNALBUS_H
#include <functional>
#include <memory>
#include <typeindex>
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
    static std::unique_ptr<SignalBus>                                              m_instance;
    std::unordered_map<std::type_index, std::vector<std::unique_ptr<BaseHandler>>> m_handlers;

  public:
    static SignalBus &create();
    static SignalBus &get();

    template <typename SignalType>
    void subscribe(const std::function<void(const SignalType &)> &handler);
    template <typename SignalType>
    void unsubscribeAll(const std::function<void(const SignalType &)> &handler);
    template <typename SignalType>
    void publish(const SignalType &signal);
};

#endif // CLICKER_SIGNALBUS_H
