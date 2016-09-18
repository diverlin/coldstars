#pragma once

#include "Base.hpp"

namespace descriptor {

class DescriptorOLD : public BaseOLD {
public:
    DescriptorOLD(const int_t&, const int_t&);
    DescriptorOLD(const std::string& data);
};

} // namespace descriptor
