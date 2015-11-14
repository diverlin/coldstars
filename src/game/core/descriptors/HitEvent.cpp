#include "HitEvent.hpp"

#include <sstream>

HitEvent::HitEvent(const ID& agressor, const ID& victim, int damage)
    :
      agressor(agressor),
      victim(victim),
      damage(damage)
{}

HitEvent::HitEvent(const std::string& data) {
    std::stringstream ss;
    ss << data;
    boost::archive::text_iarchive ia(ss);
    ia >> *this;
}

std::string HitEvent::data() const {
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}


