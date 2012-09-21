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

#include "BaseItem.hpp"
#include "../common/constants.hpp"
#include "../common/EntityManager.hpp"
#include "../slots/ItemSlot.hpp"
#include "../render/Render.hpp"
#include "../resources/TextureManager.hpp"
#include "../common/Logger.hpp"
#include "../common/myStr.hpp"

BaseItem::BaseItem()
{
        item_slot = NULL;
        
        functional_slot_subtype_id = NONE_ID;
        race_id = NONE_ID;
        
        condition = 0;
        price = 0;
        
        locked_turns = 0;
        
        textureOb = NULL;
}

/* virtual */
BaseItem::~BaseItem()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~BaseItem(), id="+int2str(GetId()));
	#endif
}

void BaseItem::LockEvent(int locked_turns)
{
	bool was_working = false;
	if (this->locked_turns == 0)
	{
		was_working = true;
	}
	
        this->locked_turns += locked_turns;
        if (was_working == true)
        {
        	item_slot->UpdateVehiclePropetries();        
	}
}
                
                
void BaseItem::DeteriorationEvent()
{
	if (is_DAMAGED == false)
	{
	    	condition -= data_item.deterioration_rate;
    		if (condition <= 0)
    		{
                        DamageEvent();
       		}
    	}
}


void BaseItem::DamageEvent()
{
        is_DAMAGED = true;
       	item_slot->UpdateVehiclePropetries(); 
}           
                
void BaseItem::RepairEvent()
{
    	condition = data_item.condition_max;
    	if (is_DAMAGED == true)
    	{
        	is_DAMAGED = false;
        	item_slot->UpdateVehiclePropetries();  
    	}
}

void BaseItem::UpdateLock()
{
        if (locked_turns > 0)
        {
                locked_turns--; 
                if (locked_turns == 0)
                {
                	item_slot->UpdateVehiclePropetries();
                }
        }
}     

void BaseItem::UpdateInfo()
{
	info.clear();

	AddUniqueInfo();
    	AddCommonInfo();
}

void BaseItem::RenderInfo(const Rect& rect, float offset_x, float offset_y)
{  
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, rect.GetCenter().x - offset_x, rect.GetCenter().y - offset_y);
}

/* virtual */
void BaseItem::Render(const Rect& rect, const vec2f& gui_offset, bool draw_text)
{
    	drawTexturedRect(textureOb, rect, -1.0);
}

void BaseItem::SaveDataUniqueBaseItem(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"price", price);
        save_ptree.put(root+"condition", condition);
        save_ptree.put(root+"locked_turns", locked_turns);
        save_ptree.put(root+"race_id", race_id);
        save_ptree.put(root+"functional_slot_subtype_id", functional_slot_subtype_id);
        
        save_ptree.put(root+"data_item.modules_num_max",    data_item.modules_num_max);
        save_ptree.put(root+"data_item.condition_max",      data_item.condition_max);                         
        save_ptree.put(root+"data_item.deterioration_rate", data_item.deterioration_rate);   
        save_ptree.put(root+"data_item.mass",               data_item.mass);
                    
	if (textureOb) 	save_ptree.put(root+"unresolved.textureOb_path", textureOb->path);
	else            save_ptree.put(root+"unresolved.textureOb_path", "none");
        
        if (item_slot) 	{ save_ptree.put(root+"unresolved.item_slot_id", item_slot->GetId()); }
	else           	{ save_ptree.put(root+"unresolved.item_slot_id", NONE_ID); }
}

void BaseItem::LoadDataUniqueBaseItem(const boost::property_tree::ptree& load_ptree)
{
        price = load_ptree.get<int>("price");
        condition = load_ptree.get<int>("condition");
        locked_turns = load_ptree.get<int>("locked_turns");
        race_id = load_ptree.get<int>("race_id");
        functional_slot_subtype_id = load_ptree.get<int>("functional_slot_subtype_id");
    
        data_item.modules_num_max    = load_ptree.get<int>("data_item.modules_num_max");
        data_item.condition_max      = load_ptree.get<int>("data_item.condition_max");                         
        data_item.deterioration_rate = load_ptree.get<int>("data_item.deterioration_rate");   
        data_item.mass               = load_ptree.get<int>("data_item.mass");
                    
	data_unresolved_BaseItem.textureOb_path = load_ptree.get<std::string>("unresolved.textureOb_path");
	data_unresolved_BaseItem.item_slot_id   = load_ptree.get<int>("unresolved.item_slot_id");
}
                
void BaseItem::ResolveDataUniqueBaseItem()
{
	textureOb = TextureManager::Instance().GetTextureObByPath(data_unresolved_BaseItem.textureOb_path);
		
	UpdatePropetries(); // this function must be performed before inserting to slot!!!
		
	if(data_unresolved_BaseItem.item_slot_id != NONE_ID) // item_slot can be NULL in case of inserted module
	{
		((ItemSlot*)EntityManager::Instance().GetEntityById(data_unresolved_BaseItem.item_slot_id))->InsertItem(this);
	}
}
