#pragma once

#include <types/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class HitDescriptor {
    public:
        HitDescriptor(const id_type& agressor, const id_type& victim, int damage);
        HitDescriptor(const std::string& data);

        id_type agressor = 0;
        id_type victim = 0;
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


