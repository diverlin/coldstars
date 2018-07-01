#pragma once

# include <core/communication/BTelegramHandler.hpp>

namespace core {
class Telegram;
} // naemspace core

namespace client {

class TelegramHandler : public core::BTelegramHandler
{
public:
    TelegramHandler():BTelegramHandler(core::Machine::CLIENT) {}
    virtual ~TelegramHandler()=default;

protected:
    void _process(const core::Telegram&) const override final;

//    void _createPlayer(const core::Telegram&) const;
    void _createExplosionEffect(const core::Telegram&) const;

private:
    void __handleReplyPlayerCreateNpc(const core::Telegram&) const;
    void __playerBindNpc(const core::Telegram&) const;
//    void __handleReplyPlayerCreateShip(const core::Telegram&) const;
};

} // namespace client
