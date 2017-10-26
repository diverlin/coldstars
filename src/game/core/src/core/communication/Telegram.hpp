#pragma once

#include <core/type/TelegramType.hpp>

#include <ceti/type/IdType.hpp>

#include <string>


namespace core {
namespace comm {


class Telegram
{
protected:
    enum class Address: int {SERVER, CLIENT};
    Telegram(Address reciever, telegram::Type, const std::string& data, double delay = -1.0);
public:
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
    Address m_address = Address::CLIENT;
    telegram::Type m_type = telegram::Type::NONE;
    std::string m_data = "";

    double m_delay = -1.0;
    double m_dispatchTime = 0.0;
};


class ServerTelegram : public Telegram {
public:
    ServerTelegram(telegram::Type type, const std::string& data, double delay = -1.0)
        :
          Telegram(Telegram::Address::SERVER, type, data, delay)
    {}
};

class ClientTelegram : public Telegram {
public:
    ClientTelegram(telegram::Type type, const std::string& data, double delay = -1.0)
        :
          Telegram(Telegram::Address::CLIENT, type, data, delay)
    {}
};

} // namespace comm
} // namespace core
