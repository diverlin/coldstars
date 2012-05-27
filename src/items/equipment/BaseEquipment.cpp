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


BaseEquipment::BaseEquipment()
{
        data_id.type_id = TYPE::EQUIPMENT_ID;
        race_id         = RACE::R0_ID;
          
    	is_DAMAGED = false;

    	condition       = 1000; //common_data.condition_max;
    	price = 0;
}


BaseEquipment::~BaseEquipment()
{
	//for (unsigned int i = 0; i < modules_vec.size(); i++)
	//{
		//delete modules_vec[i];
	//}
}

/* virtual */
void BaseEquipment::AddCommonInfo()
{
    	info.addNameStr("modules:");   info.addValueStr( int2str(data_item.modules_num_max) );
    	info.addNameStr("race:");      info.addValueStr( returnRaceStringByRaceId(race_id) );
    	info.addNameStr("condition:"); info.addValueStr( int2str(condition) + "/" + int2str(data_item.condition_max) );
    	info.addNameStr("mass:");      info.addValueStr( int2str(data_item.mass) );
    	info.addNameStr("price:");     info.addValueStr( int2str(price) );
}

bool BaseEquipment::InsertModule(BaseModule* module)
{
	if (modules_vec.size() < data_item.modules_num_max)
    	{
    		module->SetSlot(NULL);
	       	modules_vec.push_back(module);
        	UpdatePropetries();
        	
        	slot->UpdateOwnerAbilities();

        	return true;
    	}

       	return false;   
} 

/* virtual */
void BaseEquipment::Render(Rect slot_rect)
{
    	drawTexturedRect(textureOb, slot_rect, -1.0);
    	//if ((subtype == ROCKET_ID) or (subtype == TORPED_ID))
        	//drawSimpleText((slot_rect[0], slot_rect[1] + self.h/2), str(self.ammo_max) + '/' + str(self.ammo))
    
    	for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
        	Rect module_rect(	slot_rect.GetBottomLeft().x + (1.1 * GUI::INSERTED_MODULE_SIZE) * (i), 
        		          	slot_rect.GetBottomLeft().y + (1.1 * GUI::INSERTED_MODULE_SIZE),
        			  	GUI::INSERTED_MODULE_SIZE, 
        			  	GUI::INSERTED_MODULE_SIZE);
        	drawTexturedRect(modules_vec[i]->GetTextureOb(), module_rect, -1);
    	}
}


void BaseEquipment::SaveDataUniqueBaseEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	for (unsigned int i = 0; i < modules_vec.size(); i++)
	{
	        save_ptree.put(root+"unresolved.inserted_module."+int2str(modules_vec[i]->GetId())+".id", modules_vec[i]->GetId());
	}
}

void BaseEquipment::LoadDataUniqueBaseEquipment(const boost::property_tree::ptree& load_ptree)
{
	boost::property_tree::ptree tmp_ptree = load_ptree;
	if (tmp_ptree.get_child_optional("unresolved.inserted_module"))
	{
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, tmp_ptree.get_child("unresolved.inserted_module"))
		{
			data_unresolved_BaseEquipment.modules_id.push_back(v.second.get<int>("id"));
		}
	}
}

void BaseEquipment::ResolveDataUniqueBaseEquipment()
{
	UpdatePropetries();
	for (unsigned int i = 0; i<data_unresolved_BaseEquipment.modules_id.size(); i++)
	{
		InsertModule((BaseModule*)EntityManager::Instance().GetEntityById(data_unresolved_BaseEquipment.modules_id[i]));
	}
}
