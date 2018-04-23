#pragma once

#include <communication/BTelegramHandler.hpp>
#include <communication/TelegramCreator.hpp>

namespace core {

class TelegramHandler : public BTelegramHandler
{
public:
    TelegramHandler(TelegramCreator& telegramCreator)
        :
          BTelegramHandler(Machine::SERVER)
        , m_telegramCreator(telegramCreator)
    {}
    ~TelegramHandler()=default;

protected:
    void _process(const Telegram&) const override final;

private:
    void __playerMoveReply(const Telegram&) const;
    void __playerTurnEndReply(const Telegram&) const;
    void __playerSetSpaceObjectTargetReply(const Telegram&) const;
    void __playerCreateNpcReply(const Telegram&) const;
    void __playerBindNpcReply(const Telegram&) const;
    void __playerBindNpcAndShipReply(const Telegram&) const;

    TelegramCreator& m_telegramCreator;
};

} // namespace core
