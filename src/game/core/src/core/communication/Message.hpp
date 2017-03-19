#pragma once

#include <core/type/TelegramType.hpp>

#include <ceti/type/IdType.hpp>

#include <string>

class Message
{
public:
    Message(TELEGRAM, const std::string& data = "", double delay = -1.0);

    bool operator<(const Message&) const;

    //id_type id = 0;
    TELEGRAM type_id = TELEGRAM::NONE;
    std::string data = "";

    double delay = -1.0;
    double dispatch_time = 0.0;
};

