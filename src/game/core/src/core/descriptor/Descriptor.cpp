#include "Descriptor.hpp"

namespace descriptor {

DescriptorOLD::DescriptorOLD(int_t descriptor, int_t obj_id)
    : BaseOLD(TypeOLD::DESCRIPTOR, /*generate_id=*/false)
{
    add(Key::DESCRIPTOR, descriptor);
    add(Key::OBJ, obj_id);
}

DescriptorOLD::DescriptorOLD(const std::string& data)
    : BaseOLD(data)
{
}

} // namespace descriptor


