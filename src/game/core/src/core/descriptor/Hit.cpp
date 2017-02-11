#include "Hit.hpp"

namespace descriptor {

Hit::Hit(int_t owner, int_t target, int damage)
    : BaseOLD(Type::HIT)
{
    add(Key::OWNER, owner);
    add(Key::TARGET, target);
    add(Key::DAMAGE, damage);
}

Hit::Hit(const std::string& data)
    : BaseOLD(data)
{
}

} // namespace descriptor


