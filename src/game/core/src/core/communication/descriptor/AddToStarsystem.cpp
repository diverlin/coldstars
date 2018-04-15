#include "AddToStarsystem.hpp"

#include <ceti/serialization/macro.hpp>

namespace core {

AddToStarsystemComDescr::AddToStarsystemComDescr(int_t object,
                                 int_t parent,
                                 const meti::vec3& position,
                                 const meti::vec3& impulse,
                                 const meti::vec3& angle)
    :
      AddPositionalComDescr(object, parent, position)
    , impulse(impulse)
    , angle(angle)
{
}

AddToStarsystemComDescr::AddToStarsystemComDescr(const std::string& data) {
    MACRO_READ_SERIALIZED_DATA
}

std::string
AddToStarsystemComDescr::data() const {
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace descriptor

