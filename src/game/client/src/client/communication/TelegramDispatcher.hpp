#pragma once

# include <core/communication/TelegramDispatcher.hpp>

namespace client {
namespace comm {

class TelegramHandler : public core::comm::TelegramHandler
{
public:
    TelegramHandler()=default;
    virtual ~TelegramHandler()=default;

private:
    bool _process(const core::comm::Telegram&) override final;
};

} // namespace comm
} // namespace client
