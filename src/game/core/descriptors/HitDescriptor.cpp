#include "HitDescriptor.hpp"

#include <sstream>

HitDescriptor::HitDescriptor(const id_type& agressor, const id_type& victim, int damage)
    :
      agressor(agressor),
      victim(victim),
      damage(damage)
{}

HitDescriptor::HitDescriptor(const std::string& data) {
    std::stringstream ss;
    ss << data;
    boost::archive::text_iarchive ia(ss);
    ia >> *this;
}

std::string HitDescriptor::data() const {
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}


