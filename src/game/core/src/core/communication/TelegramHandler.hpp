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
    void __playerTurnEndReply(const Telegram& telegram) const;
    void __playerSetSpaceObjectTargetReply(const Telegram& telegram) const;

    TelegramCreator& m_telegramCreator;
};

} // namespace core
