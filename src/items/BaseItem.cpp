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

ItemCommonData :: ItemCommonData()
{	
	modules_num_max    = 0; 
	condition_max      = 0; 
	deterioration_rate = 0;
	mass               = 0; 
}	


BaseItem::BaseItem()
{
        slot = NULL;
        price = 0;
}

/* virtual */
BaseItem::~BaseItem ()
{}

void BaseItem::Deterioration()
{
	if (is_DAMAGED == false)
	{
	    	condition -= data_item.deterioration_rate;
    		if (condition <= 0)
    		{
       			is_DAMAGED = true;
       			slot->UpdateOwnerAbilities(); 
       		}
    	}
}

void BaseItem::Repair()
{
    	condition = data_item.condition_max;
    	if (is_DAMAGED == true)
    	{
        	is_DAMAGED = false;
        	slot->UpdateOwnerAbilities();   
    	}
}

void BaseItem::UpdateInfo()
{
	info.clear();

	AddUniqueInfo();
    	AddCommonInfo();
}

void BaseItem::RenderInfo(Rect slot_rect, float offset_x, float offset_y)
{  
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.GetCenter().x, slot_rect.GetCenter().y, offset_x, offset_y);
}

/* virtual */
void BaseItem::Render(Rect slot_rect)
{
    	drawTexturedRect(textureOb, slot_rect, -1.0);
}

void BaseItem::SaveDataUniqueBaseItem(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"price", price);
        save_ptree.put(root+"condition", condition);
        save_ptree.put(root+"race_id", race_id);
        save_ptree.put(root+"functional_slot_subtype_id", functional_slot_subtype_id);
        
        save_ptree.put(root+"data_item.modules_num_max",    data_item.modules_num_max);
        save_ptree.put(root+"data_item.condition_max",      data_item.condition_max);                         
        save_ptree.put(root+"data_item.deterioration_rate", data_item.deterioration_rate);   
        save_ptree.put(root+"data_item.mass",               data_item.mass);
                    
	if (textureOb) 	save_ptree.put(root+"unresolved.textureOb_path", textureOb->path);
	else            save_ptree.put(root+"unresolved.textureOb_path", "none");
        
        save_ptree.put(root+"unresolved.slot_id", slot->GetId());
}

void BaseItem::LoadDataUniqueBaseItem(const boost::property_tree::ptree& load_ptree)
{
        price = load_ptree.get<int>("price");
        condition = load_ptree.get<int>("condition");
        race_id = load_ptree.get<int>("race_id");
        functional_slot_subtype_id = load_ptree.get<int>("functional_slot_subtype_id");
    
        data_item.modules_num_max    = load_ptree.get<int>("data_item.modules_num_max");
        data_item.condition_max      = load_ptree.get<int>("data_item.condition_max");                         
        data_item.deterioration_rate = load_ptree.get<int>("data_item.deterioration_rate");   
        data_item.mass               = load_ptree.get<int>("data_item.mass");
                    
	data_unresolved_BaseItem.textureOb_path = load_ptree.get<std::string>("unresolved.textureOb_path");
	data_unresolved_BaseItem.slot_id        = load_ptree.get<int>("unresolved.slot_id");
}
                
void BaseItem::ResolveDataUniqueBaseItem()
{
	textureOb = g_TEXTURE_MANAGER.GetTextureObByPath(data_unresolved_BaseItem.textureOb_path);
	((ItemSlot*)EntityManager::Instance().GetEntityById(data_unresolved_BaseItem.slot_id))->InsertItem(this);
}
