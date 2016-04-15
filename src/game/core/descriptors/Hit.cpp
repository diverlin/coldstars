#include "Hit.hpp"

namespace descriptor {

Hit::Hit(const id_type& owner, const id_type& target, int damage)
{
    add(KEY_TYPE, int(Type::HIT));
    add(KEY_OWNER, owner);
    add(KEY_TARGET, target);
    add(KEY_DAMAGE, damage);
}

Hit::Hit(const std::string& data)
    :
    Base(data)
{
}

} // namespace descriptor


