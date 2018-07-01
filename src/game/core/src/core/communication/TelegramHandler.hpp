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
    ~TelegramHandler() override {}

protected:
    void _process(const Telegram&) const override final;

private:
    void __playerMoveReply(const Telegram&) const;
    void __playerTurnEndReply(const Telegram&) const;
    void __playerSetSpaceObjectTargetReply(const Telegram&) const;
    void __replyOnPlayerCreateNpcRequest(const Telegram&) const;
    void __replyOnPlayerCreateShipRequest(const Telegram&) const;
    void __playerBindNpc(const Telegram&) const;
//    void __playerInsertNpcToShipReply(const Telegram&) const;

    TelegramCreator& m_telegramCreator;
};

} // namespace core
