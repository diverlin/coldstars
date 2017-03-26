#pragma once

#include <ceti/type/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <glm/glm.hpp>

namespace descriptor {

class Explosion {
    public:
        Explosion(int_t starsystem_id, const glm::vec3& center, int damage, int radius);
        Explosion(const std::string& data);

        int_t starsystem_id = 0;
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

} // namespace descriptor
