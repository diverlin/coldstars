#include "Hit.hpp"

namespace descriptor {

Hit::Hit(const id_type& owner, const id_type& target, int damage)
{
    add(KEY_TYPE, std::to_string(int(Type::HIT)));
    add(KEY_OWNER, std::to_string(owner));
    add(KEY_TARGET, std::to_string(target));
    add(KEY_DAMAGE, std::to_string(damage));
}

Hit::Hit(const std::string& data)
    :
    Base(data)
{
}

} // namespace descriptor


