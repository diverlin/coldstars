#include "TelegramHandler.hpp"

namespace core {
namespace comm {

void BTelegramHandler::add(Telegram& telegramm)
{
//    if (telegramm.delay() < 0) {
//        //_process(telegramm); // cause error while simulation server+client on single machine
//    } else {
        telegramm.setDispatchTime(__currentTime() + telegramm.delay());
        m_telegrams.push_back(telegramm);
//    }
}

double BTelegramHandler::__currentTime() const
{
    return m_clock.getElapsedTime().asSeconds();
}

void BTelegramHandler::runLoop()
{
    while(!m_telegrams.empty()) {
        update();
    }
}

void BTelegramHandler::update()
{ 
    for(auto it = m_telegrams.begin(); it != m_telegrams.end(); ++it) {
        const Telegram& telegramm = *it;
        if (telegramm.dispatchTime() < __currentTime()) {
            _process(telegramm);
            m_telegrams.erase(it);
            break;
        }
    }
}

} // namespace comm
} // namespace core

