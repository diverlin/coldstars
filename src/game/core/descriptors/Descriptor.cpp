#include "Descriptor.hpp"

namespace descriptor {

Descriptor::Descriptor(const id_type& descriptor, const id_type& obj_id)
    : Base(Type::DESCRIPTOR, /*generate_id=*/false)
{
    add(Key::DESCRIPTOR, descriptor);
    add(Key::OBJ_ID, obj_id);
}

Descriptor::Descriptor(const std::string& data)
    : Base(data)
{
}

} // namespace descriptor


