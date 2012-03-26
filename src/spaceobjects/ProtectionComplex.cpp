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


ProtectionComplex::ProtectionComplex(Vehicle* vehicle)
{        
        this->owner_vehicle = vehicle;
        
        TextureOb* texOb_shield = g_TEXTURE_MANAGER.getRandomTexOb(SHIELD_EFFECT_TEXTURE_ID); 
 	shield_effect = new ShieldEffect(vehicle, texOb_shield);
 
     	TextureOb* texOb_slot   = g_TEXTURE_MANAGER.getRandomTexOb(SLOT_TEXTURE_ID); 

 	protector_slot.SetSubTypeId(SLOT::PROTECTOR_ID); 
 	protector_slot.SetTextureOb(texOb_slot);
	protector_slot.SetOwnerVehicle(vehicle);
	protector_slot.setRect(vehicle->GetGuiRect().getCenter().x - 3*SHIP_SLOT_WIDTH, 
			       vehicle->GetGuiRect().getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT,
			       SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
    	vehicle->Add(&protector_slot); 
}

ProtectionComplex::~ProtectionComplex() { delete shield_effect; }
   		      		
ItemSlot& ProtectionComplex::GetProtectorSlot() { return protector_slot; }
ShieldEffect* ProtectionComplex::GetShieldEffect() const { return shield_effect; }  
