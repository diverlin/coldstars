#pragma once

#include <types/IdType.hpp>
#include <types/TelegramTypes.hpp>

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


//class CreateStarsystemEvent {
//    public:
//        CreateStarsystemEvent(const ID& agressor, const ID& victim, int damage);
//        CreateStarsystemEvent(const std::string& data);

//        ID starsystem = 0;

//    std::string data() const;
//};

//class HitEvent {
//    public:
//        HitEvent(const ID& agressor, const ID& victim, int damage);
//        HitEvent(const std::string& data);

//        ID agressor = 0;
//        ID victim = 0;
//        int damage = 0;

//    std::string data() const;
//};


//Message getMessage(const HitEvent& hitEvent, double delay = 0.0);

