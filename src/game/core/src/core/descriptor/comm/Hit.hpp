#pragma once

#include <core/descriptor/Base.hpp>

namespace descriptor {

class Hit : public Base {
public:
    Hit(int_t agressor, int_t victim, int damage);
    Hit(const std::string&);
    std::string data() const;
    ~Hit() = default;

    int_t owner() const { return m_owner; }
    int_t target() const { return m_target; }
    int damage() const { return m_damage; }

private:
    int_t m_owner = NONE;
    int_t m_target = NONE;
    int m_damage = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_owner;
        ar & m_target;
        ar & m_damage;
    }
};

} // namespace descriptor
