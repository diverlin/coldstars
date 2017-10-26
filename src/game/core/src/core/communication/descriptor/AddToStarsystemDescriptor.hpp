#pragma once

#include <ceti/type/IdType.hpp>

#include <meti/VectorUtils.hpp>

#include <ceti/StringUtils.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <glm/glm.hpp>

class AddToStarsystemDescriptor {
public:
    AddToStarsystemDescriptor(int_t starsystem,
                              int_t object,
                              const meti::vec3& position = meti::vec3(0.0f),
                              const meti::vec3& impulse = meti::vec3(0.0f),
                              const meti::vec3& angle = meti::vec3(0.0f));

    AddToStarsystemDescriptor(const std::string& data);

    int_t starsystem = 0;
    int_t object = 0;
    meti::vec3 position;
    meti::vec3 impulse;
    meti::vec3 angle;

    std::string data() const;

    std::string info() const {
        std::string result = "AddToStarsystemDescriptor:\n";
        result += std::string(" starsystem = ") + std::to_string(starsystem) + "\n";
        result += std::string(" object = ") + std::to_string(object) + "\n";
        result += std::string(" position = ") + ceti::to_string(position) + "\n";
        result += std::string(" position = ") + ceti::to_string(impulse) + "\n";
        result += std::string(" position = ") + ceti::to_string(angle) + "\n";
        return result;
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & starsystem;
        ar & object;
        ar & position;
        ar & impulse;
        ar & angle;
    }
};


