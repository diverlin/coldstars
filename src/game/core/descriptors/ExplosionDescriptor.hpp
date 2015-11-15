#pragma once

#include <types/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <glm/glm.hpp>

class ExplosionDescriptor {
    public:
        ExplosionDescriptor(const ID& starsystem_id, const glm::vec3& center, int damage, int radius);
        ExplosionDescriptor(const std::string& data);

        ID starsystem_id = 0;
        glm::vec3 center;
        int damage = 0;
        int radius = 0;

        std::string data() const;

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & starsystem_id;
            ar & center.x;
            ar & center.y;
            ar & center.z;
            ar & damage;
            ar & radius;
        }
};


