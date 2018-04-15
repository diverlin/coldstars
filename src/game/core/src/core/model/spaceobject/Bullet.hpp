/*
    Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#pragma once

#include <core/spaceobject/SpaceObject.hpp>

#include <ceti/StringUtils.hpp>

namespace model {

class BulletModel : public SpaceObjectModel {

public:
    BulletModel();
    ~BulletModel() = default;
    BulletModel(const std::string& data);
    std::string data() const;

    void setDamage(int damage) {m_damage = damage; }
    void setOwner(int_t owner) { m_owner = owner; }
    void setTarget(int_t target) { m_target = target; }
    void setDamageRate(float damage_rate) { m_damageRate = damage_rate; }
    void setSpeed(float speed) { m_speed = speed; }

    void increaseSpeed(float d_speed) { m_speed += d_speed; }
    void decreaseLiveTime(int val) { m_liveTime -= val; }

    int damage() const { return m_damage; }
    float speed() const { return m_speed; }
    int_t owner() const { return m_owner; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = SpaceObjectModel::info();
        result.add("model::Bullet");
        result.add("damage", m_damage);
        result.add("liveTime", m_liveTime);
        result.add("speed", m_speed);
        result.add("damageRate", m_damageRate);
        result.add("owner", m_owner);
        result.add("target", m_target);
        return result;
    }

private:
    int m_damage = 0;
    int m_liveTime = 0;
    float m_speed = 0.0f;
    float m_damageRate = 0.0f;

    int_t m_owner = NONE;
    int_t m_target = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObjectModel>(*this);
        ar & m_damage;
        ar & m_liveTime;
        ar & m_speed;
        ar & m_damageRate;
        ar & m_owner;
        ar & m_target;
    }
};

} // namespace model
