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

#include "Weapon.hpp"

namespace descriptor {

class RocketDescr : public WeaponDescr
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
    RocketDescr();
    ~RocketDescr() = default;
    RocketDescr(const std::string& data);
    std::string data() const;

    void setBulletDescriptor(int_t bulletDescriptor) { m_bulletDescriptor = bulletDescriptor; }
    void setAmmo(int ammo) { m_ammo = ammo; }

    int_t bulletDescriptor() const { return m_bulletDescriptor; }
    int ammo() const { return m_ammo; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = WeaponDescr::info();
        result.add("descriptor::Rocket");
        result.add("ammo", m_ammo);
        result.add("bulletDescriptor", m_bulletDescriptor);
        return result;
    }

private:
    int m_ammo = 0;
    int_t m_bulletDescriptor = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<WeaponDescr>(*this);
        ar & m_ammo;
        ar & m_bulletDescriptor;
    }
};

} // namespace descriptor

