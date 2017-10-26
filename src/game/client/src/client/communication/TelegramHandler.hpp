#pragma once

# include <core/communication/BTelegramHandler.hpp>

namespace client {
namespace comm {

class TelegramHandler : public core::comm::BTelegramHandler
{
public:
    TelegramHandler():BTelegramHandler(core::comm::Machine::CLIENT) {}
    virtual ~TelegramHandler()=default;

protected:
    void _process(const core::comm::Telegram&) const override final;

    // player
    void _createPlayer(const core::comm::Telegram&) const;
    void _createExplosionEffect(const core::comm::Telegram&) const;
};

} // namespace comm
} // namespace client
