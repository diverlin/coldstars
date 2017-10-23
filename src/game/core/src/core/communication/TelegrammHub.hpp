#pragma once

#include <communication/Telegramm.hpp>

#include <vector>
#include <memory>

namespace core {
namespace comm {

class TelegrammHandler;

class TelegrammHub
{
public:
    TelegrammHub()=default;
    ~TelegrammHub()=default;

    void subscribe(const std::shared_ptr<TelegrammHandler>&);
    void add(const Telegramm&);

private:
    std::vector<Telegramm> m_telegramms;
    std::vector<std::shared_ptr<TelegrammHandler>> m_listeners;

    void __broadcast();

    void __update();
};

} // namespace comm
} // namespace core
