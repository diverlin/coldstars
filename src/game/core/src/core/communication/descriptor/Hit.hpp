#pragma once

#include <ceti/type/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace core {

class HitComDescr {
public:
    HitComDescr(int_t agressor, int_t victim, int damage);
    HitComDescr(const std::string&);
    std::string data() const;
    ~HitComDescr() = default;

    int_t owner() const { return m_owner; }
    int_t target() const { return m_target; }
    int damage() const { return m_damage; }

    std::string info() const {
        std::string result = "Hit:\n";
        result += std::string(" owner = ") + std::to_string(m_owner) + "\n";
        result += std::string(" target = ") + std::to_string(m_target) + "\n";
        result += std::string(" damage = ") + std::to_string(m_damage) + "\n";
        return result;
    }

private:
    int_t m_owner = NONE;
    int_t m_target = NONE;
    int m_damage = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_owner;
        ar & m_target;
        ar & m_damage;
    }
};

} // namespace core
