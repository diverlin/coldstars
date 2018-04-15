#pragma once

#include <core/communication/Telegram.hpp>

namespace client {

class Telegram : public core::Telegram {
public:
    Telegram(telegram::Type type, const std::string& data, double delay = -1.0)
        :
          core::Telegram(type, data, delay)
    {
        _setMachine(core::Machine::CLIENT);
    }
};

} // namespace client
