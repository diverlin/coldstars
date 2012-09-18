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

#include "GrappleEquipment.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"
#include "../../slots/ItemSlot.hpp"
#include "../../spaceobjects/Vehicle.hpp"
#include "../../resources/GuiTextureObCollector.hpp"
#include "../../render/Render.hpp"

GrappleEquipment::GrappleEquipment(int id)
{
        data_id.id         = id;
        data_id.subtype_id = ENTITY::GRAPPLE_EQUIPMENT_ID;
        
    	strength_orig   = 0;
    	radius_orig     = 0;
        speed_orig      = 0;
}

/* virtual */
GrappleEquipment::~GrappleEquipment()
{}

bool GrappleEquipment::CheckIfTargetAlreadyExistInQueue(BaseGameEntity* target) const
{
        for (unsigned int i=0; i<target_vec.size(); i++)
        {
                if (target_vec[i]->GetId() == target->GetId())
                {
                       	return true;  
                }    
        }  
        
        return false;    
}

void GrappleEquipment::AddTarget(BaseGameEntity* target)
{
	// avoiding dublicated items in the vector
	if (CheckIfTargetAlreadyExistInQueue(target) == true)    
	{
		return;
	}         
                
        if (free_strength > target->GetMass())
        {
                target_vec.push_back(target);
                free_strength -= target->GetMass();
                
               	#if GRAPPLE_QUEUE_LOG_ENABLED == 1 
		Logger::Instance().Log("vehicle_id=" + int2str(item_slot->GetOwnerVehicle()->GetId()) + " " + getEntityStr(target->GetTypeId()) + " id = " + int2str(target->GetId()) + " grapple->AddTarget()", 2); 
		#endif
        }        
}

void GrappleEquipment::RemoveTarget(BaseGameEntity* target)
{
        for (unsigned int i=0; i<target_vec.size(); i++)
        {
                if (target_vec[i]->GetId() == target->GetId())
                {
                       	target_vec.erase(target_vec.begin()+i);
                        free_strength += target->GetMass();
                        
                        return;  
                }    
        }  
}     
 
void GrappleEquipment::RemoveAllTargets()
{
        target_vec.clear(); 
        free_strength = strength;
}
                              
std::string GrappleEquipment::GetTargetStr() const
{
	std::string str = "";
	
        for (unsigned int i=0; i<target_vec.size(); i++)
        {
		str += int2str(target_vec[i]->GetId()) + ", ";
        }
                
        return str;
}
 
        
void GrappleEquipment::UpdateGrabScenarioProgram()
{               
        for (std::vector<BaseGameEntity*>::iterator it = target_vec.begin(); it != target_vec.end(); ++it)
        {
        	if (item_slot->CheckTarget(*it) == true)
        	{
               		(*it)->MovingByExternalForce(item_slot->GetOwnerVehicle()->GetPoints().GetCenter(), GetStrength());        	
       	
       			float dist = distBetweenPoints(item_slot->GetOwnerVehicle()->GetPoints().GetCenter(), (*it)->GetPoints().GetCenter()); 
       			if (dist < item_slot->GetOwnerVehicle()->GetCollisionRadius()/2.0f)
       			{
       				switch((*it)->GetTypeId())
       				{
      					case ENTITY::CONTAINER_ID:
       					{
       						Container* container = (Container*)(*it);
       						if (item_slot->GetOwnerVehicle()->UnpackContainerItemToCargoSlot(container) == true)
						{
                                                        it = target_vec.erase(it);
                                                        return; // hack
       						}
       					
       						break;
       					}
        				
       					//case ENTITY::VEHICLE_ID:
       					//{
       						//ItemSlot* _slot = GetEmptyOtsecSlot();
                                        	//Vehicle* _vehicle = (Vehicle*)grapple_slot->GetGrappleEquipment()->target_vec[i];
       				        	//if (_slot != NULL)
       						//{
       							////_slot->InsertItem(_vehicle);
       							//starsystem->AddToRemoveFromOuterSpaceQueue(_vehicle);
       						//}
						//grapple_slot->GetGrappleEquipment()->AddToRemoveQueue(_vehicle);
       						//break;
       					//}
       				}
       			}
       		}
       		else
       		{
                        #if GRAPPLE_QUEUE_LOG_ENABLED == 1 
			Logger::Instance().Log("vehicle_id=" + int2str(item_slot->GetOwnerVehicle()->GetId()) + " " + getEntityStr((*it)->GetTypeId()) + " id = " + int2str((*it)->GetId()) + " grapple->RemoveTarget()", 2); 
			#endif
                        
                        it = target_vec.erase(it);
                        return; // hack
       		}
       	}
}

void GrappleEquipment::RenderGrabTrail() const
{
        for (unsigned int i=0; i<target_vec.size(); i++)
        {
               	float xl = target_vec[i]->GetPoints().GetCenter().x - item_slot->GetOwnerVehicle()->GetPoints().GetCenter().x;
                float yl = target_vec[i]->GetPoints().GetCenter().y - item_slot->GetOwnerVehicle()->GetPoints().GetCenter().y;

                float len = sqrt((xl*xl) + (yl*yl));

                float angle_inR = atan2(yl, xl);

                float angle_inD = angle_inR * RADIAN_TO_DEGREE_RATE;
        
                drawLine(GuiTextureObCollector::Instance().grapple_trail, 
                         item_slot->GetOwnerVehicle()->GetPoints().GetCenter(), 
                         item_slot->GetOwnerVehicle()->GetPoints().GetPosZ(), 
                         len, 
                         angle_inD, 
                         8);
        }
}


/* virtual */
void GrappleEquipment::UpdatePropetries()
{
    	strength_add   = 0;
    	radius_add     = 0;
   	speed_add      = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		strength_add   += ((GrappleModule*)modules_vec[i])->GetStrengthAdd();
        	radius_add     += ((GrappleModule*)modules_vec[i])->GetRadiusAdd();        	
        	speed_add      += ((GrappleModule*)modules_vec[i])->GetSpeedAdd();
    	}
    		        	
    	strength   = strength_orig   + strength_add;
    	radius     = radius_orig     + radius_add;
    	speed      = speed_orig      + speed_add;
        
        RemoveAllTargets();
}

void GrappleEquipment::CountPrice()
{
    	float strength_rate      = (float)strength_orig / EQUIPMENT::GRAPPLE::STRENGTH_MIN;
    	float radius_rate        = (float)radius_orig / EQUIPMENT::GRAPPLE::RADIUS_MIN;
    	float speed_rate         = (float)speed_orig / EQUIPMENT::GRAPPLE::SPEED_MIN;

    	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::GRAPPLE::MODULES_NUM_MAX;

    	float effectiveness_rate = EQUIPMENT::GRAPPLE::STRENGTH_WEIGHT * strength_rate + 
    				   EQUIPMENT::GRAPPLE::RADIUS_WEIGHT * radius_rate + 
    				   EQUIPMENT::GRAPPLE::SPEED_WEIGHT * speed_rate + 
    				   EQUIPMENT::GRAPPLE::MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)data_item.mass / EQUIPMENT::GRAPPLE::MASS_MIN;
    	float condition_rate     = (float)condition / data_item.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void GrappleEquipment::AddUniqueInfo()
{    	
	info.addTitleStr("GRAPPLE");

    	info.addNameStr("strength:");        info.addValueStr(GetStrengthStr() + "/" + int2str(free_strength));
    	info.addNameStr("radius:");          info.addValueStr(GetRadiusStr());
    	info.addNameStr("speed:");           info.addValueStr(GetSpeedStr());
}

std::string GrappleEquipment::GetStrengthStr()
{
     	if (strength_add == 0)
        	return int2str(strength_orig);
     	else
        	return int2str(strength_orig) + "+" + int2str(strength_add);
}

std::string GrappleEquipment::GetRadiusStr()
{
     	if (radius_add == 0)
        	return int2str(radius_orig);
     	else
        	return int2str(radius_orig) + "+" + int2str(radius_add);
}

std::string GrappleEquipment::GetSpeedStr()
{
     	if (speed_add == 0)
        	return int2str(speed_orig);
     	else
        	return int2str(speed_orig) + "+" + int2str(speed_add);
}

/*virtual*/
void GrappleEquipment::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "grapple_equipment." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseEquipment(save_ptree, root);
	SaveDataUniqueGrappleEquipment(save_ptree, root);
}

/*virtual*/
void GrappleEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseEquipment(load_ptree);
	LoadDataUniqueGrappleEquipment(load_ptree);
}

/*virtual*/
void GrappleEquipment::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseEquipment();
	ResolveDataUniqueGrappleEquipment();
}

void GrappleEquipment::SaveDataUniqueGrappleEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"strength_orig", strength_orig);
        save_ptree.put(root+"radius_orig", radius_orig);
        save_ptree.put(root+"speed_orig", speed_orig);
}
                
void GrappleEquipment::LoadDataUniqueGrappleEquipment(const boost::property_tree::ptree& load_ptree)
{
        strength_orig = load_ptree.get<int>("strength_orig");     
        radius_orig = load_ptree.get<int>("radius_orig");   
        speed_orig = load_ptree.get<int>("speed_orig");           
}                

void GrappleEquipment::ResolveDataUniqueGrappleEquipment()
{}

