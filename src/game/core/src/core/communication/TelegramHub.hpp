#pragma once

#include <communication/Telegram.hpp>

#include <vector>
#include <memory>

namespace core {
namespace comm {

class TelegramHandler;

class TelegramHub
{
public:
    TelegramHub()=default;
    ~TelegramHub()=default;

    void subscribe(const std::shared_ptr<TelegramHandler>&);
    void add(const Telegram&);

    void broadcast();

private:
    std::vector<Telegram> m_telegramms;
    std::vector<std::shared_ptr<TelegramHandler>> m_listeners;
//    void __update();
};

} // namespace comm
} // namespace core
