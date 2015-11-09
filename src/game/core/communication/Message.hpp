#pragma once

/*
long int    enum     long int   long int    void
[MSG_ID]-[TYPE_ID]-[SENDER_ID]-[RECEVER_ID]-[DATA]
*/

#include <types/IdType.hpp>
#include <types/TelegramTypes.hpp>

class Message
{
    public:
        Message(TELEGRAM, const ID&, const ID&, const std::string&, double delay = 0.0);
//        Message(const Message&);

        //bool operator()(const Message&) {};
        bool operator<(const Message&) const;        

        ID id = 0;
        TELEGRAM type_id = TELEGRAM::NONE;
        ID sender_id = 0;
        ID receiver_id = 0;
        std::string extra = "";

        double delay = 0.0;
        double dispatch_time = 0.0;
};                       
