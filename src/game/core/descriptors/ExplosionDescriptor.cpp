#include "ExplosionDescriptor.hpp"
#include <serialization/Serialization.hpp>

#include <sstream>

namespace descriptor {

Explosion::Explosion(const id_type& starsystem_id, const glm::vec3& center, int damage, int radius)
    :
      starsystem_id(starsystem_id),
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
