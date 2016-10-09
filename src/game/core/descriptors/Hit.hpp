#pragma once

#include "Base.hpp"

namespace descriptor {

class Hit : public BaseOLD {
public:
    Hit(int_t agressor, int_t victim, int damage);
    Hit(const std::string& data);
};

} // namespace descriptor
