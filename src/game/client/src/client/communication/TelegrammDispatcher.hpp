#pragma once

# include <core/communication/TelegrammDispatcher.hpp>

namespace client {
namespace comm {

class TelegrammHandler : public core::comm::TelegrammHandler
{
public:
    TelegrammHandler()=default;
    virtual ~TelegrammHandler()=default;

private:
    bool _process(const core::comm::Telegramm&) override final;
};

} // namespace comm
} // namespace client
