#pragma once

#include "Base.hpp"

namespace descriptor {

class DescriptorOLD : public BaseOLD {
public:
    DescriptorOLD(int_t, int_t);
    DescriptorOLD(const std::string& data);
};

} // namespace descriptor
