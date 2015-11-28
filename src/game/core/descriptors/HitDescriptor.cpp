#include "HitDescriptor.hpp"
#include <serialization/Serialization.hpp>

#include <sstream>

HitDescriptor::HitDescriptor(const id_type& agressor, const id_type& victim, int damage)
    :
      agressor(agressor),
      victim(victim),
      damage(damage)
{}

HitDescriptor::HitDescriptor(const std::string& data) {
    MACRO_READ_SERIALIZED_DATA
}

std::string HitDescriptor::data() const {
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}


