#pragma once

#include <communication/BTelegramHandler.hpp>
#include <communication/TelegramHub.hpp>

namespace core {
namespace comm {

class TelegramHandler : public BTelegramHandler
{
public:
    TelegramHandler(TelegramHub& telegramHub)
        :
          BTelegramHandler(Machine::SERVER)
        , m_telegramHub(telegramHub)
    {}
    ~TelegramHandler()=default;

protected:
    void _process(const Telegram&) const override final;

private:
    void __playerMoveReply(const Telegram&) const;
    TelegramHub& m_telegramHub;
};

} // namespace comm
} // namespace core
