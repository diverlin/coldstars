#pragma once

#include "Base.hpp"

namespace descriptor {

class DescriptorOLD : public Base {
public:
    DescriptorOLD(const id_type&, const id_type&);
    DescriptorOLD(const std::string& data);
};

} // namespace descriptor
