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


#ifndef PROTECTIONCOMPLEX_H
#define PROTECTIONCOMPLEX_H

class Vehicle;
class ShieldEffect; 
class ItemSlot; 

class ProtectionComplex
{
    public:
              ProtectionComplex();
              ~ProtectionComplex();

                   void SetOwnerVehicle(Vehicle* owner_vehicle) { this->owner_vehicle = owner_vehicle; };
              void SetProtectorSlot(ItemSlot* protector_slot) { this->protector_slot = protector_slot; };
    
              ItemSlot* GetProtectorSlot()    const { return protector_slot; };
            ShieldEffect* GetShieldEffect() const { return shield_effect; }; 
            
          private:
              Vehicle* owner_vehicle;
            
            ItemSlot* protector_slot;
            ShieldEffect* shield_effect;
};


#endif
