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
        Message(TELEGRAM, const id_type&, const id_type&, void*);
//        Message(const Message&);

        //bool operator()(const Message&) {};
        bool operator<(const Message&) const;
        
        //double delay;
        id_type id;
        TELEGRAM type_id;
        id_type sender_id;
        id_type receiver_id;
        void*  extra;
        
        double dispatch_time;
};                       
