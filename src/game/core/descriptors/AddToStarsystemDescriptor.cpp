#include "AddToStarsystemDescriptor.hpp"

#include <ceti/serialization/macro.hpp>

AddToStarsystemDescriptor::AddToStarsystemDescriptor(const int_t& owner,
                                                     const int_t& object,
                                                     const glm::vec3& position,
                                                     const glm::vec3& angle)
    :
      owner(owner)
    , object(object)
    , position(position)
    , angle(angle)
{}

AddToStarsystemDescriptor::AddToStarsystemDescriptor(const std::string& data) {
    MACRO_READ_SERIALIZED_DATA
}

std::string
AddToStarsystemDescriptor::data() const {
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}


