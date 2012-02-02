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


Turrel :: Turrel(ItemSlot* _slot, vec2f* _pCenter)
{
        slot = _slot;
        
    	//////
    	points.addCenterPoint();
    	points.addMainQuadPoints();
    	//////   
                 
        pCenter  = _pCenter;
        
        targetOb = new TargetObject();
}


Turrel :: ~Turrel()
{
        delete targetOb;
}

void Turrel :: setSelectedStatus(bool _selected) { is_SELECTED = _selected; }    
            
bool Turrel :: getSelectedStatus() const { return is_SELECTED; }
vec2f* Turrel :: getpCenter() const      { return pCenter; }
vec2f Turrel :: getCenter() const        { return points.getCenter(); }
float Turrel :: getAngle()   const       { return points.getAngleDegree(); }
  
TargetObject* Turrel :: getTargetOb() { return targetOb; }

void Turrel :: setTexOb(TextureOb* _texOb)
{
    	texOb = _texOb;

    	//////
    	points.initCenterPoint();
    	points.initMainQuadPoints(texOb->w, texOb->h);
    	//////
}


bool Turrel :: validateTarget()
{
        slot->targetObValidation(targetOb);    
                        
    	return targetOb->getValid();
}




bool Turrel :: isAmmoAvailable()
{
	switch(slot->getItemSubTypeId() )
	{
    		case LAZER_EQUIPMENT_ID:  { /*if check energy */  return true; }
    		case ROCKET_EQUIPMENT_ID: { if (slot->getRocketEquipment()->getAmmo() > 0) return true; }
	}
	
    	return false;           
}




bool Turrel :: fireEvent_TRUE()
{
	switch(slot->getItemSubTypeId())
	{
    		case LAZER_EQUIPMENT_ID:
    		{   
       			slot->getLazerEquipment()->fireEvent_TRUE();

			switch(targetOb->getObTypeId())
			{
				case SHIP_ID:      { targetOb->getVehicle()->hit_TRUE(slot->getLazerEquipment()->getDamage());   return true; break; }
       				case ASTEROID_ID:  { targetOb->getAsteroid()->hit_TRUE(slot->getLazerEquipment()->getDamage());  return true; break; }
				case MINERAL_ID:   { targetOb->getMineral()->hit_TRUE(slot->getLazerEquipment()->getDamage());   return true; break; }
				case CONTAINER_ID: { targetOb->getContainer()->hit_TRUE(slot->getLazerEquipment()->getDamage()); return true; break; }
				case BOMB_ID:      { targetOb->getBomb()->hit_TRUE(slot->getLazerEquipment()->getDamage());    	 return true; break; }
       			}
       			
       			break;
    		}

    		case ROCKET_EQUIPMENT_ID:
    		{       
                	slot->getRocketEquipment()->fireEvent_TRUE();
                	return true; break;              
    		}

	}
	
    	return false;
}





bool Turrel :: fireEvent_FALSE()
{
	switch(slot->getItemSubTypeId())
	{
    		case LAZER_EQUIPMENT_ID:
    		{   
   			slot->getLazerEquipment()->fireEvent_FALSE();

			switch(targetOb->getObTypeId())
			{
				case SHIP_ID:      { targetOb->getVehicle()->hit_FALSE(slot->getLazerEquipment()->getDamage());   return true; break; }
       				case ASTEROID_ID:  { targetOb->getAsteroid()->hit_FALSE(slot->getLazerEquipment()->getDamage());  return true; break; }
				case MINERAL_ID:   { targetOb->getMineral()->hit_FALSE(slot->getLazerEquipment()->getDamage());   return true; break; }
				case CONTAINER_ID: { targetOb->getContainer()->hit_FALSE(slot->getLazerEquipment()->getDamage()); return true; break; }
				case BOMB_ID:      { targetOb->getBomb()->hit_FALSE(slot->getLazerEquipment()->getDamage());      return true; break; }
       			}
       			
       			break;
    		}

    		case ROCKET_EQUIPMENT_ID:
    		{       
                	slot->getRocketEquipment()->fireEvent_FALSE();
                	return true; break;            
    		}

	}
	
    	return false;
}



                              
template<typename TARGET_TYPE>
void Turrel :: setTarget(TARGET_TYPE* _target)
{
     	targetOb->setObject(_target);
}



void Turrel :: render(float _tur_angle_inD)
{        
        if (targetOb->getValid() == true)
        {
        	float _tur_xl = targetOb->getpCenter()->x - pCenter->x;
        	float _tur_yl = targetOb->getpCenter()->y - pCenter->y;

        	float _tur_angle_inR = atan2(_tur_yl, _tur_xl);
        	_tur_angle_inD = _tur_angle_inR * RADIAN_TO_DEGREE_RATE;
        }

	//printf("xy target =%f,%f\n", turrel_center_pList[i]->x, turrel_center_pList[i]->y);
                    	
        points.setCenter(pCenter->x, pCenter->y);
    	points.setAngle(_tur_angle_inD);
    	points.update();
        

    	drawFlatQuadPerVertexIn2D(texOb,
    				  points.getBottomLeft(), 
                                  points.getBottomRight(), 
                                  points.getTopRight(), 
                                  points.getTopLeft(), 
                                  points.getPosZ());
}        
                
