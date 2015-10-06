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
        Message(TELEGRAM, const IDTYPE&, const IDTYPE&, void*);
//        Message(const Message&);

        //bool operator()(const Message&) {};
        bool operator<(const Message&) const;
        
        //double delay;
        IDTYPE id;
        TELEGRAM type_id;
        IDTYPE sender_id;
        IDTYPE receiver_id;
        void*  extra;
        
        double dispatch_time;
};                       
