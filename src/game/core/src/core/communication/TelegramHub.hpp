#pragma once

#include <communication/Telegram.hpp>

#include <ceti/Pack.hpp>

#include <vector>
#include <memory>

namespace core {

class BTelegramHandler;

class TelegramHub
{
public:
    TelegramHub()=default;
    ~TelegramHub()=default;

    void subscribe(const std::shared_ptr<BTelegramHandler>&);
    void unsubscribe(const std::shared_ptr<BTelegramHandler>&);

    void add(const Telegram&);

    void broadcast();

private:
    ceti::pack<Telegram> m_telegrams;
    ceti::pack<std::shared_ptr<BTelegramHandler>> m_listeners;
};

} // namespace core
