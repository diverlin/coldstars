#include "TelegrammHub.hpp"

#include <core/communication/TelegrammManager.hpp>

namespace core {
namespace comm {

void TelegrammHub::add(TelegrammDispatcher* listener)
{
    m_listeners.push_back(listener);
}

void TelegrammHub::add(const Telegramm& telegramm)
{
    m_telegramms.push_back(telegramm);
    __update();
}

void TelegrammHub::__update()
{
    __broadcast();
    for (TelegrammDispatcher* listener: m_listeners) {
        listener->update();
    }
}

void TelegrammHub::__broadcast()
{
    for (TelegrammDispatcher* listener: m_listeners) {
        for(Telegramm& telegramm: m_telegramms) {
            listener->add(telegramm);
        }
    }
    m_telegramms.clear();
}

} // namespace comm
} // namespace core

