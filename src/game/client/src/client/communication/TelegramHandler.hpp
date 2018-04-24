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

    // player
    void _createPlayer(const core::Telegram&) const;
    void _createExplosionEffect(const core::Telegram&) const;
    void __replyPlayerCreateNpc(const core::Telegram&) const;
};

} // namespace client
