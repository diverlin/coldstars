#include "Hit.hpp"

namespace descriptor {

Hit::Hit(const id_type& owner, const id_type& target, int damage)
{
    add(Key::TYPE, int(Type::HIT));
    add(Key::OWNER, owner);
    add(Key::TARGET, target);
    add(Key::DAMAGE, damage);
}

Hit::Hit(const std::string& data)
    :
    Base(data)
{
}

} // namespace descriptor


