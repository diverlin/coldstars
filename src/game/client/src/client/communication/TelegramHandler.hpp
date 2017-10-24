#pragma once

# include <core/communication/BTelegramHandler.hpp>

namespace client {
namespace comm {

class TelegramHandler : public core::comm::BTelegramHandler
{
public:
    TelegramHandler()=default;
    virtual ~TelegramHandler()=default;

protected:
    void _process(const core::comm::Telegram&) const override final;
};

} // namespace comm
} // namespace client
