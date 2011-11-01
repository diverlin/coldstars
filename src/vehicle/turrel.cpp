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
        
        targetOb = new TargetObject(slot);
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


bool Turrel :: fireCheck()
{
        targetOb->validation(*pCenter);    
                        
    	return targetOb->getValid();
}




bool Turrel :: isAmmoAvailable()
{
    	if (slot->getItemSubTypeId() == LAZER_ID)
                //if check energy
                        return true;
    	if (slot->getItemSubTypeId() == ROCKET_ID)
       		if (slot->getRocketEquipment()->getAmmo() > 0)
          		return true;

    	return false;           
}




bool Turrel :: fireEvent_TRUE()
{
    	if (slot->getItemSubTypeId() == LAZER_ID)
    	{   
       		slot->getLazerEquipment()->fireEvent(this);

       		if (targetOb->getObTypeId() == SHIP_ID) 
       		{ 
           		targetOb->getShip()->hit_TRUE(slot->getLazerEquipment()->getDamage());
           		return true;
       		} 

       		if (targetOb->getObTypeId() == ASTEROID_ID)  
       		{ 
           		targetOb->getAsteroid()->hit_TRUE(slot->getLazerEquipment()->getDamage());
           		return true;
       		}

       		if (targetOb->getObTypeId() == MINERAL_ID)  
       		{ 
           		targetOb->getMineral()->hit_TRUE(slot->getLazerEquipment()->getDamage());
           		return true;
       		}

       		if (targetOb->getObTypeId() == CONTAINER_ID)  
       		{ 
           		targetOb->getContainer()->hit_TRUE(slot->getLazerEquipment()->getDamage());
           		return true;
       		}
    	}

    	if (slot->getItemSubTypeId() == ROCKET_ID)
    	{       
                slot->getRocketEquipment()->fireEvent();
                return true;                
    	}

    	return false;
}





bool Turrel :: fireEvent_FALSE()
{
   	return fireEvent_TRUE();
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
        
                
   	glBindTexture(GL_TEXTURE_2D, texOb->texture); 
    	drawFlatQuadPerVertexIn2D(points.getBottomLeft(), 
                                  points.getBottomRight(), 
                                  points.getTopRight(), 
                                  points.getTopLeft(), 
                                  points.getPosZ());
}        
                
