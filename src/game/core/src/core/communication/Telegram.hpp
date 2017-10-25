#pragma once

#include <core/type/TelegramType.hpp>

#include <ceti/type/IdType.hpp>

#include <string>


namespace core {
namespace comm {

class Telegram
{
public:
    Telegram(telegram::Type, const std::string& data = "", double delay = -1.0);

    bool operator<(const Telegram&) const;

    telegram::Type type() const { return m_type; }
    std::string data() const { return m_data; }
    double delay() const { return m_delay; }
    double dispatchTime() const { return m_dispatchTime; }

    void setDispatchTime(double dispatchTime) {
        m_dispatchTime = dispatchTime;
    }

private:
    //id_type id = 0;
    telegram::Type m_type = telegram::Type::NONE;
    std::string m_data = "";

    double m_delay = -1.0;
    double m_dispatchTime = 0.0;
};

} // namespace comm
} // namespace core