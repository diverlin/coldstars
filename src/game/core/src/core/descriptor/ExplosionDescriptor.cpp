#include "ExplosionDescriptor.hpp"

#include <ceti/serialization/macro.hpp>

#include <sstream>

namespace descriptor {

Explosion::Explosion(int_t starsystem_id, const glm::vec3& center, int damage, int radius)
    :
      starsystem(starsystem_id),
      center(center),
      damage(damage),
      radius(radius)
{}

Explosion::Explosion(const std::string& data) {
    MACRO_READ_SERIALIZED_DATA
}

std::string Explosion::data() const {
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace descriptor
