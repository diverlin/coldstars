#pragma once

# include <core/communication/TelegrammManager.hpp>

namespace client {
namespace comm {

class TelegrammDispatcher : public core::comm::TelegrammDispatcher
{
public:
    TelegrammDispatcher()=default;
    virtual ~TelegrammDispatcher()=default;

private:
    bool _process(const core::comm::Telegramm&) override final;
};

} // namespace comm
} // namespace client
