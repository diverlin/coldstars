#pragma once

# include <core/communication/TelegrammManager.hpp>

namespace client {
namespace comm {

class TelegrammManager : public core::comm::TelegrammManager
{
public:
    TelegrammManager()=default;
    virtual ~TelegrammManager()=default;

private:
    bool _process(const core::comm::Telegramm&) override final;
};

} // namespace comm
} // namespace client
