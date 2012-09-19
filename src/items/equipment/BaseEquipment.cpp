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

#include "BaseEquipment.hpp"
#include "RocketEquipment.hpp"

#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../slots/ItemSlot.hpp"
#include "../../render/Render.hpp"
#include "../../resources/GuiTextureObCollector.hpp"

BaseEquipment::BaseEquipment()
{
        data_id.type_id = ENTITY::EQUIPMENT_ID;
        race_id         = RACE::R0_ID;
          
    	is_DAMAGED = false;

    	price = 0;
}


BaseEquipment::~BaseEquipment()
{}

/* virtual */
void BaseEquipment::AddCommonInfo()
{
    	info.addNameStr("modules:");   info.addValueStr( int2str(data_item.modules_num_max) );
    	info.addNameStr("race:");      info.addValueStr( getRaceStr(race_id) );
    	info.addNameStr("condition:"); info.addValueStr( int2str(condition) + "/" + int2str(data_item.condition_max) );
    	info.addNameStr("mass:");      info.addValueStr( int2str(data_item.mass) );
    	info.addNameStr("price:");     info.addValueStr( int2str(price) );
    	info.addNameStr("damaged:");   info.addValueStr( int2str(is_DAMAGED) );
}

bool BaseEquipment::InsertModule(BaseModule* module)
{
	if (modules_vec.size() < data_item.modules_num_max)
    	{
    		module->SetItemSlot(NULL);
    		module->SetEquipmentOwner(this);
	       	modules_vec.push_back(module);                
                        
        	UpdatePropetries();
        	item_slot->UpdateVehiclePropetries();

        	return true;
    	}

       	return false;   
} 

/* virtual */
void BaseEquipment::Render(const Rect& rect, const vec2f& gui_offset, bool draw_text)
{
    	drawTexturedRect(textureOb, rect, -1.0);
    
    	for (unsigned int i=0; i<modules_vec.size(); i++)
    	{
        	Rect module_rect(rect.GetBottomLeft().x + (1.1 * GUI::INSERTED_MODULE_SIZE) * (i), 
        		         rect.GetBottomLeft().y + (1.1 * GUI::INSERTED_MODULE_SIZE),
        			 GUI::INSERTED_MODULE_SIZE, 
        			 GUI::INSERTED_MODULE_SIZE);
        	drawTexturedRect(modules_vec[i]->GetTextureOb(), module_rect, -1);
    	}
    	
    	if (is_DAMAGED == true)
	{
    		drawTexturedRect(GuiTextureObCollector::Instance().slot_mark_reject , rect, -1.0);	
	}
	if (locked_turns != 0)
	{
    		drawTexturedRect(GuiTextureObCollector::Instance().slot_mark_accept, rect, -1.0);
    		drawSimpleText(int2str(locked_turns), 12, rect.GetCenter().x + gui_offset.x, rect.GetCenter().y + gui_offset.y);	
	}

	if (draw_text == true)
	{
    		if (data_id.subtype_id == ENTITY::ROCKET_EQUIPMENT_ID)
        	{
        		drawSimpleText(int2str(((RocketEquipment*)this)->GetAmmoMax()) + '/' + int2str(((RocketEquipment*)this)->GetAmmo()), 12, rect.GetCenter().x - rect.GetWidth()/2 + gui_offset.x, rect.GetCenter().y + gui_offset.y);
		}
	}
}


void BaseEquipment::SaveDataUniqueBaseEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void BaseEquipment::LoadDataUniqueBaseEquipment(const boost::property_tree::ptree& load_ptree)
{}

void BaseEquipment::ResolveDataUniqueBaseEquipment()
{}
