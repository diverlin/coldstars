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


GrappleEquipment::GrappleEquipment(int id)
{
        data_id.id         = id;
        data_id.subtype_id = SUBTYPE::GRAPPLE_ID;
        
    	strength_orig   = 0;
    	radius_orig     = 0;
        speed_orig      = 0;
    	maxNumItem_orig = 0;
}

/* virtual */
GrappleEquipment::~GrappleEquipment()
{}

void GrappleEquipment::AddTarget(BaseGameEntity* target)
{
	// avoiding dublicated items in the vector
        for (unsigned int i=0; i<target_vec.size(); i++)
        {
                if (target_vec[i]->GetId() == target->GetId() )
                {
                       	return;  
                }    
        }                
                
        if (target_vec.size() < maxNumItem)
        {
                target_vec.push_back(target);
                
               	#if GRAPPLE_QUEUE_LOG_ENABLED == 1 
		Logger::Instance().Log("vehicle_id=" + int2str(item_slot->GetOwnerVehicle()->GetId()) + " " + getEntityStr(target->GetTypeId()) + " id = " + int2str(target->GetId()) + " ADDED to grapple queue", 2); 
		#endif
        }        
}

void GrappleEquipment::AddToRemoveQueue(BaseGameEntity* target)
{
        remove_queue.push_back(target);
}

void GrappleEquipment::ClearRemoveQueue()
{
        for (unsigned int i=0; i<remove_queue.size(); i++)
        {
                for (unsigned int j=0; j<target_vec.size(); j++)
                {
                        if (remove_queue[i]->GetId() == target_vec[j]->GetId())
                        {
                                target_vec.erase(target_vec.begin() + j);
                                break;                                
                        }
                }
        }
}
                
std::string GrappleEquipment::GetTargetStr() const
{
	std::string str = "";
	
        for (unsigned int i = 0; i < target_vec.size(); i++)
        {
        	if (target_vec[i]) // hack, validator should be deal this
        	{
       			str += "c" + int2str(target_vec[i]->GetId()) + ", ";
        	}
        }
        
        return str;
}
 
        
void GrappleEquipment::UpdateGrabScenarioProgram()
{               
        for (unsigned int i=0; i<target_vec.size(); i++)
        {
        	if (item_slot->CheckTarget(target_vec[i]) == true)
        	{
               		target_vec[i]->MovingByExternalForce(item_slot->GetOwnerVehicle()->GetPoints().GetCenter(), GetStrength());        	
       	
       			float dist = distBetweenPoints(item_slot->GetOwnerVehicle()->GetPoints().GetCenter(), target_vec[i]->GetPoints().GetCenter() ); 
       			if (dist < item_slot->GetOwnerVehicle()->GetCollisionRadius()/2.0f)
       			{
       				switch(target_vec[i]->GetTypeId())
       				{
      					case ENTITY::CONTAINER_ID:
       					{
       						Container* container = (Container*)target_vec[i];
       						if (item_slot->GetOwnerVehicle()->UnpackContainerItemToCargoSlot(container) == true)
						{
							AddToRemoveQueue(target_vec[i]);
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
       		        AddToRemoveQueue(target_vec[i]);

                        #if GRAPPLE_QUEUE_LOG_ENABLED == 1 
			Logger::Instance().Log("vehicle_id=" + int2str(item_slot->GetOwnerVehicle()->GetId()) + " " + getEntityStr(target_vec[i]->GetTypeId()) + " id = " + int2str(target_vec[i]->GetId()) + " ADDED to grapple REMOVE queue", 2); 
			#endif
       		}
       	}

        ClearRemoveQueue(); 
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
   	maxNumItem_add = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		strength_add   += ((GrappleModule*)modules_vec[i])->GetStrengthAdd();
        	radius_add     += ((GrappleModule*)modules_vec[i])->GetRadiusAdd();        	
        	speed_add      += ((GrappleModule*)modules_vec[i])->GetSpeedAdd();
        	maxNumItem_add += ((GrappleModule*)modules_vec[i])->GetMaxNumItemAdd();
    	}
    		        	
    	strength   = strength_orig   + strength_add;
    	radius     = radius_orig     + radius_add;
    	speed      = speed_orig      + speed_add;
    	maxNumItem = maxNumItem_orig + maxNumItem_add;
}

void GrappleEquipment::CountPrice()
{
    	float strength_rate      = (float)strength_orig / EQUIPMENT::GRAPPLE::STRENGTH_MIN;
    	float radius_rate        = (float)radius_orig / EQUIPMENT::GRAPPLE::RADIUS_MIN;
    	float speed_rate         = (float)speed_orig / EQUIPMENT::GRAPPLE::SPEED_MIN;
    	float maxNumItem_rate    = (float)maxNumItem_orig / EQUIPMENT::GRAPPLE::MAXNUMITEM_MIN;

    	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::GRAPPLE::MODULES_NUM_MAX;

    	float effectiveness_rate = EQUIPMENT::GRAPPLE::STRENGTH_WEIGHT * strength_rate + 
    				   EQUIPMENT::GRAPPLE::RADIUS_WEIGHT * radius_rate + 
    				   EQUIPMENT::GRAPPLE::SPEED_WEIGHT * speed_rate + 
    				   EQUIPMENT::GRAPPLE::MAXNUMITEM_WEIGHT * maxNumItem_rate + 
    				   EQUIPMENT::GRAPPLE::MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)data_item.mass / EQUIPMENT::GRAPPLE::MASS_MIN;
    	float condition_rate     = (float)condition / data_item.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void GrappleEquipment::AddUniqueInfo()
{    	
	info.addTitleStr("GRAPPLE");

    	info.addNameStr("strength:");    info.addValueStr(GetStrengthStr());
    	info.addNameStr("radius:");      info.addValueStr(GetRadiusStr());
    	info.addNameStr("speed:");       info.addValueStr(GetSpeedStr());
    	info.addNameStr("maxNumItem:");  info.addValueStr(GetMaxNumItemStr());
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

std::string GrappleEquipment::GetMaxNumItemStr()
{
     	if (maxNumItem_add == 0)
        	return int2str(maxNumItem_orig);
     	else
        	return int2str(maxNumItem_orig) + "+" + int2str(maxNumItem_add);
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
        save_ptree.put(root+"maxNumItem_orig", maxNumItem_orig);
}
                
void GrappleEquipment::LoadDataUniqueGrappleEquipment(const boost::property_tree::ptree& load_ptree)
{
        strength_orig = load_ptree.get<int>("strength_orig");     
        radius_orig = load_ptree.get<int>("radius_orig");   
        speed_orig = load_ptree.get<int>("speed_orig");           
        maxNumItem_orig = load_ptree.get<int>("maxNumItem_orig");   
}                

void GrappleEquipment::ResolveDataUniqueGrappleEquipment()
{}

