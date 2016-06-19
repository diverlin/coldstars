#pragma once

#include "Base.hpp"

namespace descriptor {

class Descriptor : public Base {
public:
    Descriptor(const id_type&, const id_type&);
    Descriptor(const std::string& data);
};

} // namespace descriptor
