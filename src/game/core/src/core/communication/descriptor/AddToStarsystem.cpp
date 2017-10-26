#include "AddToStarsystem.hpp"

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace comm {

AddToStarsystem::AddToStarsystem(int_t object,
                                 int_t parent,
                                 const meti::vec3& position,
                                 const meti::vec3& impulse,
                                 const meti::vec3& angle)
    :
      AddPositional(object, parent, position)
    , impulse(impulse)
    , angle(angle)
{
}

AddToStarsystem::AddToStarsystem(const std::string& data) {
    MACRO_READ_SERIALIZED_DATA
}

std::string
AddToStarsystem::data() const {
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace comm
} // namespace descriptor

