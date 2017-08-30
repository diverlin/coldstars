#pragma once

#include <communication/Telegramm.hpp>

#include <vector>

namespace core {
namespace comm {

class TelegrammDispatcher;

class TelegrammHub
{
public:
    TelegrammHub()=default;
    ~TelegrammHub()=default;

    void add(TelegrammDispatcher*);
    void add(const Telegramm&);

private:
    std::vector<Telegramm> m_telegramms;
    std::vector<TelegrammDispatcher*> m_listeners;

    void __broadcast();

    void __update();
};

} // namespace comm
} // namespace core
