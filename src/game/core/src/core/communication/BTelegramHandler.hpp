#pragma once


#include <communication/Telegram.hpp>

#include <SFML/System/Clock.hpp>

#include <set>

namespace core {
namespace comm {

class BTelegramHandler
{
public:
    BTelegramHandler() {}
    virtual ~BTelegramHandler() {}

    void add(Telegram&);

    [[deprecated("remove this shit, used only it tests, write helper function in tests instead")]]
    void runLoop();
    void update();

protected:
    virtual void _process(const Telegram&) const = 0;

private:
    sf::Clock m_clock;
    std::set<Telegram> m_telegramms;

    double __currentTime() const;
};

} // namespace comm
} // namespace core
