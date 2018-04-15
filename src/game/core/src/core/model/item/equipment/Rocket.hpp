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

namespace model {

class Rocket : public Weapon
{
public:
    Rocket(int_t, int_t);
    ~Rocket() = default;
    Rocket(const std::string& data);
    std::string data() const;

    void setAmmo(int ammo) { m_ammo = ammo; }

    int ammo() const { return m_ammo; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = Weapon::info();
        result.add("model::Rocket");
        result.add("ammo", m_ammo);
        return result;
    }

private:
    int m_ammo = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Weapon>(*this);
        ar & m_ammo;
    }
};

} // namespace model

