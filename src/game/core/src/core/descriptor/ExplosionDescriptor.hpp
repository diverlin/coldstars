#pragma once

#include <ceti/type/IdType.hpp>
#include <ceti/StringUtils.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <glm/glm.hpp>

namespace descriptor {

class Explosion {
public:
    Explosion(int_t starsystem, const glm::vec3& center, int damage, int radius);
    Explosion(const std::string& data);

    int_t starsystem = 0;
    glm::vec3 center;
    int damage = 0;
    int radius = 0;

    std::string data() const;

    std::string info() const {
        std::string result = "descriptor::Explosion:\n";
        result += std::string(" starsystem = ") + std::to_string(starsystem) + "\n";
        result += std::string(" center = ") + ceti::to_string(center) + "\n";
        result += std::string(" damage = ") + std::to_string(damage) + "\n";
        result += std::string(" radius = ") + std::to_string(radius) + "\n";
        return result;
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & starsystem;
        ar & center.x;
        ar & center.y;
        ar & center.z;
        ar & damage;
        ar & radius;
    }
};

} // namespace descriptor
