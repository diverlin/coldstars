#pragma once

#include "Base.hpp"

namespace descriptor {

class Hit : public Base {
public:
    Hit(const id_type& agressor, const id_type& victim, int damage);
    Hit(const std::string& data);
};

} // namespace descriptor
