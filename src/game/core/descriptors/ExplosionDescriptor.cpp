#include "ExplosionDescriptor.hpp"
#include <serialization/Serialization.hpp>

#include <sstream>

ExplosionDescriptor::ExplosionDescriptor(const id_type& starsystem_id, const glm::vec3& center, int damage, int radius)
    :
      starsystem_id(starsystem_id),
      center(center),
      damage(damage),
      radius(radius)
{}

ExplosionDescriptor::ExplosionDescriptor(const std::string& data) {
    MACRO_READ_SERIALIZED_DATA
}

std::string ExplosionDescriptor::data() const {
    MACRO_SAVE_SERIALIZED_DATA
}


