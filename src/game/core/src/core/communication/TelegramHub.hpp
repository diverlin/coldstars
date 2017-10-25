#pragma once

#include <communication/Telegram.hpp>

#include <vector>
#include <memory>

namespace core {
namespace comm {

class BTelegramHandler;

class TelegramHub
{
public:
    TelegramHub()=default;
    ~TelegramHub()=default;

    void subscribe(const std::shared_ptr<BTelegramHandler>&);
    void add(const Telegram&);

    void broadcast();

private:
    std::vector<Telegram> m_telegrams;
    std::vector<std::shared_ptr<BTelegramHandler>> m_listeners;
};

} // namespace comm
} // namespace core