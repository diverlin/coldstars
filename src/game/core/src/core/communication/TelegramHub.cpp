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
    for(Telegram& telegram: m_telegrams) {
        for (const std::shared_ptr<BTelegramHandler>& listener: m_listeners) {
            if (telegram.sender() == Machine::SERVER) { // server broadcast to everything, even itself
                listener->add(telegram);
            } else { // if Sender is client, only server must receive it
                if (listener->machine() == Machine::SERVER) {
                    listener->add(telegram);
                }
            }
        }
    }
    m_telegrams.clear();
}

} // namespace comm
} // namespace core

