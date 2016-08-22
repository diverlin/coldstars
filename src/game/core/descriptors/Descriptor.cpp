#include "Descriptor.hpp"

namespace descriptor {

DescriptorOLD::DescriptorOLD(const id_type& descriptor, const id_type& obj_id)
    : Base(Type::DESCRIPTOR, /*generate_id=*/false)
{
    add(Key::DESCRIPTOR, descriptor);
    add(Key::OBJ_ID, obj_id);
}

DescriptorOLD::DescriptorOLD(const std::string& data)
    : Base(data)
{
}

} // namespace descriptor


