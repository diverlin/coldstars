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

#include <core/common/BulletData.hpp>

#include "Weapon.hpp"

namespace descriptor {
namespace item {

class Rocket : public Weapon
{
public:
    static const int AMMO_MIN;
    static const int AMMO_MAX;
    static const float AMMO_TECH_RATE;

    static const int RADIUS_MIN;
    static const int RADIUS_MAX;
    static const float RADIUS_TECH_RATE;

    static const int DAMAGE_MIN;
    static const int DAMAGE_MAX;
    static const float DAMAGE_TECH_RATE;

    static const int MODULES_NUM_MIN;
    static const int MODULES_NUM_MAX;

    static const int MASS_MIN;
    static const int MASS_MAX;
    static const int CONDITION_MIN;
    static const int CONDITION_MAX;

    static const float AMMO_WEIGHT;
    static const float DAMAGE_WEIGHT;
    static const float RADIUS_WEIGHT;
    static const float MODULES_NUM_WEIGHT;

public:
    Rocket();
    ~Rocket() = default;
    Rocket(const std::string& data);
    std::string data() const;

    void setAmmo(int ammo) { m_ammo = ammo; }
    void setBulletData(const BulletData& bulletData) { m_data_bullet = bulletData; }

    int ammo() const { return m_ammo; }
    const BulletData& bulletData() const{ return m_data_bullet; }

    std::string info() const {
        std::string result = "descriptor::item::Rocket:\n";
        result += std::string(" ammo = ") + std::to_string(m_ammo) + "\n";
        result += m_data_bullet.info();
        result += Weapon::info();
        return result;
    }

private:
    int m_ammo = 0;
    BulletData m_data_bullet;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Weapon>(*this);
        ar & m_ammo;
        ar & m_data_bullet;
    }
};

} // namespace item
} // namespace descriptor

