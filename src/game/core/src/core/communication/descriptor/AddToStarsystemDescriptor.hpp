#pragma once

#include "AddingPositional.hpp"

#include <ceti/type/IdType.hpp>

//#include <meti/VectorUtils.hpp>

#include <ceti/StringUtils.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <glm/glm.hpp>

namespace descriptor {
namespace comm {

class AddToStarsystemDescriptor : public AddingPositional {
public:
    AddToStarsystemDescriptor(int_t object,
                              int_t parent,
                              const meti::vec3& position = meti::vec3(0.0f),
                              const meti::vec3& impulse = meti::vec3(0.0f),
                              const meti::vec3& angle = meti::vec3(0.0f));

    AddToStarsystemDescriptor(const std::string& data);

    meti::vec3 impulse;
    meti::vec3 angle;

    std::string data() const;

    std::string info() const {
        std::string result = AddingPositional::info();
        result += "descriptor::comm::AddToStarsystemDescriptor:\n";
        result += std::string(" impulse = ") + ceti::to_string(impulse) + "\n";
        result += std::string(" angle = ") + ceti::to_string(angle) + "\n";
        return result;
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<AddingPositional>(*this);
        ar & impulse;
        ar & angle;
    }
};

} // namespace comm
} // namespace descriptor
