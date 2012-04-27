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
        
 	shield_effect = new ShieldEffect();
        TextureOb* texOb_shield = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::SHIELD_EFFECT_ID); 
        shield_effect->SetTextureOb(texOb_shield);
        shield_effect->SetParent(vehicle);
        
        shield_effect->GetPoints().initMainQuadPoints(1.2*vehicle->GetTextureOb()->getFrameWidth(), 1.2*vehicle->GetTextureOb()->getFrameHeight());
    	shield_effect->GetPoints().addMainQuadPoints();
        
        protector_slot = NULL;
}

ProtectionComplex::~ProtectionComplex() 
{ 
        //delete protector_slot;
        delete shield_effect; 
}

