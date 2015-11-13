#pragma once

#include <types/IdType.hpp>
#include <types/TelegramTypes.hpp>

#include <string>

class Message
{
    public:
        Message(TELEGRAM, const std::string& data = "", double delay = 0.0);

        bool operator<(const Message&) const;        

        //ID id = 0;
        TELEGRAM type_id = TELEGRAM::NONE;
        std::string data = "";

        double delay = 0.0;
        double dispatch_time = 0.0;
};

