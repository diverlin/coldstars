#include "ExplosionDescriptor.hpp"

#include <sstream>

ExplosionDescriptor::ExplosionDescriptor(const id_type& starsystem_id, const glm::vec3& center, int damage, int radius)
    :
      starsystem_id(starsystem_id),
      center(center),
      damage(damage),
      radius(radius)
{}

ExplosionDescriptor::ExplosionDescriptor(const std::string& data) {
    std::stringstream ss;
    ss << data;
    boost::archive::text_iarchive ia(ss);
    ia >> *this;
}

std::string ExplosionDescriptor::data() const {
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}


