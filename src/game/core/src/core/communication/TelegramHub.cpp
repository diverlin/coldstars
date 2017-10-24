#include "TelegramHub.hpp"

#include <core/communication/BTelegramHandler.hpp>

namespace core {
namespace comm {

void TelegramHub::subscribe(const std::shared_ptr<BTelegramHandler>& listener)
{
    m_listeners.push_back(listener);
}

void TelegramHub::add(const Telegram& telegramm)
{
    m_telegramms.push_back(telegramm);
    //__update();
}

//void TelegramHub::__update()
//{
//    __broadcast();
//    for (const std::shared_ptr<TelegramHandler>& listener: m_listeners) {
//        listener->update();
//    }
//}

void TelegramHub::broadcast()
{
    for (const std::shared_ptr<BTelegramHandler>& listener: m_listeners) {
        for(Telegram& telegramm: m_telegramms) {
            listener->add(telegramm);
        }
    }
    m_telegramms.clear();
}

} // namespace comm
} // namespace core

