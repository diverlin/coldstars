#pragma once

#include <communication/BTelegramHandler.hpp>

namespace core {
namespace comm {

class TelegramHandler : public BTelegramHandler
{
public:
    TelegramHandler():BTelegramHandler(Machine::SERVER) {}
    virtual ~TelegramHandler()=default;

protected:
    void _process(const Telegram&) const override final;
};

} // namespace comm
} // namespace core
