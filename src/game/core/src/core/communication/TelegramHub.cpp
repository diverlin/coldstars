#include "TelegramHub.hpp"

#include <core/communication/BTelegramHandler.hpp>

#include <ceti/Logger.hpp>

namespace core {
namespace comm {

void TelegramHub::subscribe(const std::shared_ptr<BTelegramHandler>& listener)
{
    m_listeners.push_back(listener);
}

void TelegramHub::add(const Telegram& telegram)
{
    //LOG_COMM("--server: TelegramHub got telegram "+telegram::to_string(telegram.type()));
    m_telegrams.push_back(telegram);
}

void TelegramHub::broadcast()
{
    for (const std::shared_ptr<BTelegramHandler>& listener: m_listeners) {
        for(Telegram& telegram: m_telegrams) {
            listener->add(telegram);
        }
    }
    m_telegrams.clear();
}

} // namespace comm
} // namespace core

