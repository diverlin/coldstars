#pragma once

#include "Base.hpp"

namespace descriptor {

class Hit : public BaseOLD {
public:
    Hit(const int_t& agressor, const int_t& victim, int damage);
    Hit(const std::string& data);
};

} // namespace descriptor
