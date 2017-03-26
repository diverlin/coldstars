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

//namespace control {
//class Vehicle;
//} // namespace control

#include <vector>

namespace control {
class ItemSlot; 
} // namespace control

class ProtectionComplex
{
public:
    ProtectionComplex();
    ~ProtectionComplex();

//    void setOwnerVehicle(control::Vehicle* owner_vehicle) { m_owner_vehicle = owner_vehicle; }
    void addProtectorSlot(control::ItemSlot* slot) { m_protectorSlots.push_back(slot); }

    std::vector<control::ItemSlot*> protectorSlots() const { return m_protectorSlots; }
    //        ShieldEffect* GetShieldEffect() const { return shield_effect; }

private:
//    control::Vehicle* m_owner_vehicle = nullptr;

    std::vector<control::ItemSlot*> m_protectorSlots;
    //            ShieldEffect* shield_effect;
};


