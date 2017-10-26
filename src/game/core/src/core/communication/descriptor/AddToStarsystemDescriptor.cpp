#include "AddToStarsystemDescriptor.hpp"

#include <ceti/serialization/macro.hpp>

AddToStarsystemDescriptor::AddToStarsystemDescriptor(int_t owner,
                                                     int_t object,
                                                     const meti::vec3& position,
                                                     const meti::vec3& impulse,
                                                     const meti::vec3& angle)
    :
      starsystem(owner)
    , object(object)
    , position(position)
    , impulse(impulse)
    , angle(angle)
{
}

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


