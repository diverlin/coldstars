#include "AddToStarsystemDescriptor.hpp"

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace comm {

AddToStarsystemDescriptor::AddToStarsystemDescriptor(int_t object,
                                                     int_t parent,
                                                     const meti::vec3& position,
                                                     const meti::vec3& impulse,
                                                     const meti::vec3& angle)
    :
      AddingPositional(object, parent, position)
    , impulse(impulse)
    , angle(angle)
{
}

AddToStarsystemDescriptor::AddToStarsystemDescriptor(const std::string& data) {
    MACRO_READ_SERIALIZED_DATA
}

std::string
AddToStarsystemDescriptor::data() const {
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace comm
} // namespace descriptor

