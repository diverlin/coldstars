#include "AddToStarsystemDescriptor.hpp"
#include <serialization/Serialization.hpp>

#include <sstream>

AddToStarsystemDescriptor::AddToStarsystemDescriptor(const id_type& owner, const id_type& object, const glm::vec3& position, const glm::vec3& angle)
    :
      owner(owner),
      object(object),
      position(position),
      angle(angle)
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


