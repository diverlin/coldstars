#include "Hit.hpp"

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace comm {

Hit::Hit(int_t owner, int_t target, int damage)
    :
      m_owner(owner)
    , m_target(target)
    , m_damage(damage)
{
    setType(Type::HIT);
}

Hit::Hit(const std::string& data) {
    MACRO_READ_SERIALIZED_DATA
}

std::string
Hit::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace comm
} // namespace descriptor


