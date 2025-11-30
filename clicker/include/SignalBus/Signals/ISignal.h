//
// Created by XL1TTE on 30.11.2025.
//

#ifndef CLICKER_ISIGNAL_H
#define CLICKER_ISIGNAL_H

#define REGISTER_SIGNAL(signal_type)                                                                               \
    template SignalBus::Handler<signal_type>::Handler(std::function<void(const signal_type &)> callback);          \
    template void SignalBus::subscribe<signal_type>(const std::function<void(const signal_type &)> &handler);      \
    template void SignalBus::unsubscribeAll<signal_type>(const std::function<void(const signal_type &)> &handler); \
    template void SignalBus::publish<signal_type>(const signal_type &signal);

class ISignal
{
};

#endif // CLICKER_ISIGNAL_H
