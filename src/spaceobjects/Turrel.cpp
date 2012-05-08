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


Turrel::Turrel(ItemSlot* slot)
{
        this->slot = slot;
      
        target  = NULL;
}

Turrel::~Turrel()
{}

void Turrel::CheckTarget()
{
        if (target != NULL)
        {
                if (slot->CheckTarget(target) == true)
                {
                        return;
                }
                else
                {
                        ResetTarget();
                }
        }
}


bool Turrel::CheckAmmo() const
{
	switch(slot->GetItem()->GetSubTypeId())
	{
    		case SUBTYPE::LAZER_ID:  { /*if check energy */  return true; break; }
    		case SUBTYPE::ROCKET_ID: { if (slot->GetRocketEquipment()->GetAmmo() > 0) return true; break; }
	}
	
    	return false;           
}

bool Turrel::FireEvent(bool show_effect)
{
	switch(slot->GetItem()->GetSubTypeId())
	{
    		case SUBTYPE::LAZER_ID:
    		{   
       			slot->GetLazerEquipment()->FireEvent_TRUE();

			switch(target->GetTypeId())
			{
				case ENTITY::SHIP_ID:      { ((Vehicle*)target)->Hit(slot->GetLazerEquipment()->GetDamage(), show_effect);   return true; break; }
       				case ENTITY::ASTEROID_ID:  { ((Asteroid*)target)->Hit(slot->GetLazerEquipment()->GetDamage(), show_effect);  return true; break; }
				case ENTITY::CONTAINER_ID: { ((Container*)target)->Hit(slot->GetLazerEquipment()->GetDamage(), show_effect); return true; break; }
				case ENTITY::BOMB_ID:      { ((Container*)target)->Hit(slot->GetLazerEquipment()->GetDamage(), show_effect);      return true; break; }
       			}
       			
       			break;
    		}

    		case SUBTYPE::ROCKET_ID:
    		{       
                	slot->GetRocketEquipment()->FireEvent();
                	return true; break;              
    		}

	}
	
    	return false;
}


void Turrel::Render(float _tur_angle_inD)
{        
        if (target != NULL)
        {
        	float _tur_xl = target->GetPoints().GetCenter().x - points.GetCenter().x;
        	float _tur_yl = target->GetPoints().GetCenter().y - points.GetCenter().y;

        	float _tur_angle_inR = atan2(_tur_yl, _tur_xl);
        	_tur_angle_inD = _tur_angle_inR * RADIAN_TO_DEGREE_RATE;
        }

    	points.SetAngle(_tur_angle_inD);
    	points.Update();        

    	drawFlatQuadPerVertexIn2D(textureOb,
    				  points.GetBottomLeft(), 
                                  points.GetBottomRight(), 
                                  points.GetTopRight(), 
                                  points.GetTopLeft(), 
                                  points.GetPosZ());
}        
                
