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


GrappleEquipment :: GrappleEquipment(int strength_orig, 
				     int radius_orig, 
				     int speed_orig, 
				     int maxNumItem_orig)   // joun strength and speed attributes into one
{
    	this->strength_orig   = strength_orig;
    	this->radius_orig     = radius_orig;
        this->speed_orig      = speed_orig;
    	this->maxNumItem_orig = maxNumItem_orig;
}

/* virtual */
GrappleEquipment :: ~GrappleEquipment()
{}

//void GrappleEquipment :: reshapeTargetObSlot(ItemSlot* _slot)
//{
        //for (unsigned int i = 0; i < target_vec.size(); i++)
        //{
        //        target_vec[i]->bindSlot(_slot);
        //}
//}

void GrappleEquipment :: addTarget(BaseGameEntity* _target)
{
        validateTargets();
        
	// avoiding dublicated items in the vector
        for (unsigned int i = 0; i < target_vec.size(); i++)
        {
                if (target_vec[i]->getId() == _target->getId() )
                {
                       	return;  
                }    
        }                
                
        if (target_vec.size() < maxNumItem)
        {
                target_vec.push_back(_target);
        }        
}

void GrappleEquipment :: addToRemoveQueue(BaseGameEntity* target)
{
        remove_queue.push_back(target);
}

void GrappleEquipment :: validateTargets()
{
        for (unsigned int i = 0; i < target_vec.size(); i++)
        {
                if (slot->isTargetOk(target_vec[i]) == false)
                {
                        remove_queue.push_back(target_vec[i]);
                }                
        }
        
        clearRemoveQueue();        
}


void GrappleEquipment :: clearRemoveQueue()
{
        for (unsigned int i = 0; i < remove_queue.size(); i++)
        {
                for (unsigned int j = 0; j < target_vec.size(); j++)
                {
                        if (remove_queue[i] == target_vec[j])
                        {
                                target_vec.erase(target_vec.begin() + j);
                                break;                                
                        }
                }
        }
}

                
std::string GrappleEquipment :: getTargetStr() const
{
	std::string str = "";
	
        for (unsigned int i = 0; i < target_vec.size(); i++)
        {
        	if (target_vec[i]) // hack, validator should be deal this
        	{
        	switch(target_vec[i]->getTypeId())
        	{
        		case ENTITY::MINERAL:
        		{
        			str += "m" + int2str(target_vec[i]->getTypeId()) + ", ";
        			break;
        		}
        		
        		case ENTITY::CONTAINER:
        		{
        			str += "c" + int2str(target_vec[i]->getTypeId()) + ", ";
        			break;
        		}
        		        		
        		case ENTITY::BOMB:
        		{
        			str += "b" + int2str(target_vec[i]->getTypeId()) + ", ";
        			break;
        		}
        	}
        	}
        }
        
        return str;
}
                
int GrappleEquipment :: getStrength()   const { return strength; }
int GrappleEquipment :: getRadius()     const { return radius; }
int GrappleEquipment :: getSpeed()      const { return speed; }
int GrappleEquipment :: getMaxNumItem() const { return maxNumItem; }
 
/* virtual */
void GrappleEquipment :: updatePropetries()
{
    	strength_add   = 0;
    	radius_add     = 0;
   	speed_add      = 0;
   	maxNumItem_add = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		strength_add   += ((GrappleModule*)modules_vec[i])->getStrengthAdd();
        	radius_add     += ((GrappleModule*)modules_vec[i])->getRadiusAdd();        	
        	speed_add      += ((GrappleModule*)modules_vec[i])->getSpeedAdd();
        	maxNumItem_add += ((GrappleModule*)modules_vec[i])->getMaxNumItemAdd();
    	}
    		        	
    	strength   = strength_orig   + strength_add;
    	radius     = radius_orig     + radius_add;
    	speed      = speed_orig      + speed_add;
    	maxNumItem = maxNumItem_orig + maxNumItem_add;
}

void GrappleEquipment :: countPrice()
{
    	float strength_rate      = (float)strength_orig / GRAPPLE_STRENGTH_MIN;
    	float radius_rate        = (float)radius_orig / GRAPPLE_RADIUS_MIN;
    	float speed_rate         = (float)speed_orig / GRAPPLE_SPEED_MIN;
    	float maxNumItem_rate    = (float)maxNumItem_orig / GRAPPLE_MAXNUMITEM_MIN;

    	float modules_num_rate   = (float)common_data.modules_num_max / GRAPPLE_MODULES_NUM_MAX;

    	float effectiveness_rate = GRAPPLE_STRENGTH_WEIGHT * strength_rate + GRAPPLE_RADIUS_WEIGHT * radius_rate + GRAPPLE_SPEED_WEIGHT * speed_rate + GRAPPLE_MAXNUMITEM_WEIGHT * maxNumItem_rate + GRAPPLE_MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)common_data.mass / GRAPPLE_MASS_MIN;
    	float condition_rate     = (float)condition / common_data.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

/* virtual */
void GrappleEquipment :: updateOwnerAbilities()
{
    	slot->getOwnerVehicle()->UpdateGrabAbility();
}


void GrappleEquipment :: addUniqueInfo()
{    	
	info.addTitleStr("GRAPPLE");

    	info.addNameStr("strength:");    info.addValueStr( getStrengthStr() );
    	info.addNameStr("radius:");      info.addValueStr( getRadiusStr() );
    	info.addNameStr("speed:");       info.addValueStr( getSpeedStr() );
    	info.addNameStr("maxNumItem:");  info.addValueStr( getMaxNumItemStr() );
}


std::string GrappleEquipment :: getStrengthStr()
{
     	if (strength_add == 0)
        	return int2str(strength_orig);
     	else
        	return int2str(strength_orig) + "+" + int2str(strength_add);
}

std::string GrappleEquipment :: getRadiusStr()
{
     	if (radius_add == 0)
        	return int2str(radius_orig);
     	else
        	return int2str(radius_orig) + "+" + int2str(radius_add);
}

std::string GrappleEquipment :: getSpeedStr()
{
     	if (speed_add == 0)
        	return int2str(speed_orig);
     	else
        	return int2str(speed_orig) + "+" + int2str(speed_add);
}

std::string GrappleEquipment :: getMaxNumItemStr()
{
     	if (maxNumItem_add == 0)
        	return int2str(maxNumItem_orig);
     	else
        	return int2str(maxNumItem_orig) + "+" + int2str(maxNumItem_add);
}


              

GrappleEquipment* getNewGrappleEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(GRAPPLE_ITEM_TEXTURE_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(GRAPPLE_ITEM_TEXTURE_ID, revision_id) 

    	int strength_orig   = getRandInt(GRAPPLE_STRENGTH_MIN, GRAPPLE_STRENGTH_MAX);
    	int radius_orig     = getRandInt(GRAPPLE_RADIUS_MIN, GRAPPLE_RADIUS_MAX);
    	int speed_orig      = getRandInt(GRAPPLE_SPEED_MIN, GRAPPLE_SPEED_MAX);
    	int maxNumItem_orig = getRandInt(GRAPPLE_MAXNUMITEM_MIN, GRAPPLE_MAXNUMITEM_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(GRAPPLE_MODULES_NUM_MIN, GRAPPLE_MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(GRAPPLE_MASS_MIN, GRAPPLE_MASS_MAX);
    	common_data.condition_max   = getRandInt(GRAPPLE_CONDITION_MIN, GRAPPLE_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT::EQUIPMENT;
        data_id.subtype_id = EQUIPMENT::GRAPPLE;
        
    	GrappleEquipment* grapple_equipment = new GrappleEquipment(strength_orig, 
    								   radius_orig, 
    								   speed_orig, 
    								   maxNumItem_orig);                                                                   
        grapple_equipment->setIdData(data_id);  
        grapple_equipment->setTextureOb(texOb_item);    	
        grapple_equipment->setFunctionalSlotSubTypeId(SLOT::GRAPPLE);
        grapple_equipment->setItemCommonData(common_data);        

    	grapple_equipment->updatePropetries();
    	grapple_equipment->countPrice();

    	return grapple_equipment;
}
