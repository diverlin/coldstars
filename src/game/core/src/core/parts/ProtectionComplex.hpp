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

class Vehicle;
class ItemSlot; 

class ProtectionComplex
{
    public:
        ProtectionComplex();
        ~ProtectionComplex();

        void SetOwnerVehicle(Vehicle* owner_vehicle) { m_owner_vehicle = owner_vehicle; }
        void SetProtectorSlot(ItemSlot* protector_slot) { m_protector_slot = protector_slot; }

        ItemSlot* protectorSlot()    const { return m_protector_slot; }
//        ShieldEffect* GetShieldEffect() const { return shield_effect; }

    private:
        Vehicle* m_owner_vehicle;

        ItemSlot* m_protector_slot;
        //            ShieldEffect* shield_effect;
};


