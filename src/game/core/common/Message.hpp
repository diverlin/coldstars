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
        Message(TELEGRAM, const ID&, const ID&, void*);
//        Message(const Message&);

        //bool operator()(const Message&) {};
        bool operator<(const Message&) const;
        
        //double delay;
        ID id;
        TELEGRAM type_id;
        ID sender_id;
        ID receiver_id;
        void*  extra;
        
        double dispatch_time;
};                       
