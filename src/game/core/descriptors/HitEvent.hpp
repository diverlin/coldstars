#pragma once

#include <types/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class HitEvent {
    public:
        HitEvent(const ID& agressor, const ID& victim, int damage);
        HitEvent(const std::string& data);

        ID agressor = 0;
        ID victim = 0;
        int damage = 0;

        std::string data() const;

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & agressor;
            ar & victim;
            ar & damage;
        }
};


