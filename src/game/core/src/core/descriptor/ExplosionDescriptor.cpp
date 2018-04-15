#include "ExplosionDescriptor.hpp"

#include <ceti/serialization/macro.hpp>

#include <sstream>

namespace core {

ExplosionDescr::ExplosionDescr(int_t starsystem_id, const glm::vec3& center, int damage, int radius)
    :
      starsystem(starsystem_id),
      center(center),
      damage(damage),
      radius(radius)
{}

ExplosionDescr::ExplosionDescr(const std::string& data) {
    MACRO_READ_SERIALIZED_DATA
}

std::string ExplosionDescr::data() const {
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace core
