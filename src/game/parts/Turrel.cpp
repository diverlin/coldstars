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

#include "Turrel.hpp"
#include "../items/equipment/RocketEquipment.hpp"
#include "../items/equipment/LazerEquipment.hpp"
#include "../slots/ItemSlot.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../common/myStr.hpp"
#include "../common/Logger.hpp"

#include "../world/starsystem.hpp"
#include "../render/Render.hpp"
#include "../pilots/Npc.hpp"

Turrel::Turrel(ItemSlot* slot)
{
        this->slot = slot;
}

Turrel::~Turrel()
{}

void Turrel::SetTextureOb(TextureOb* textureOb)	
{ 
	this->textureOb = textureOb; 
	points.SetScale(textureOb->GetFrameWidth(), textureOb->GetFrameHeight(), 1.0); 
}

void Turrel::Render(float _tur_angle_inD)
{        
        if (slot->GetTarget() != NULL)
        {
        	float _tur_xl = slot->GetTarget()->GetPoints().GetCenterXY().x - points.GetCenterXY().x;
        	float _tur_yl = slot->GetTarget()->GetPoints().GetCenterXY().y - points.GetCenterXY().y;

        	float _tur_angle_inR = atan2(_tur_yl, _tur_xl);
        	_tur_angle_inD = _tur_angle_inR * RADIAN_TO_DEGREE_RATE;
        }     

    	drawQuad_inXYPlane(textureOb, points.GetScale(), points.GetCenter(), _tur_angle_inD);
    	//drawFlatQuadPerVertexIn2D(textureOb,
    				  //points.GetBottomLeft(), 
                                  //points.GetBottomRight(), 
                                  //points.GetTopRight(), 
                                  //points.GetTopLeft(), 
                                  //points.GetPosZ());
}        
                
