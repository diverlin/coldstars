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
#include "../../render/Screen.hpp"
#include "../../resources/GuiTextureObCollector.hpp"
#include "../../common/Logger.hpp"
#include "../../garbage/EntityGarbage.hpp"

#include "../../render/AnimationEffect2D.hpp"

BaseEquipment::BaseEquipment()
{
        data_id.type_id = ENTITY::EQUIPMENT_ID;
        race_id         = RACE::R0_ID;

    	price = 0;
    	
    	animation_notfunctioning = new AnimationEffect2D(Vec2<float>(0.8, 0.8), Vec2<float>(1.2, 1.2), Vec2<float>(0.02, 0.02), 0, 0, 0);
}

/*virtual */
BaseEquipment::~BaseEquipment()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~BaseEquipment("+int2str(GetId())+")");
	#endif
    	
    	delete animation_notfunctioning;
}

/* virtual */
void BaseEquipment::PutChildsToGarbage() const
{
	for (unsigned int i=0; i<modules_vec.size(); i++)
	{
		EntityGarbage::Instance().Add(modules_vec[i]);
	}
}
		
/* virtual */
void BaseEquipment::AddCommonInfo()
{
    	info.addNameStr("tech_level:");   info.addValueStr( int2str(data_item.tech_level) );
    	info.addNameStr("modules:");   info.addValueStr( int2str(data_item.modules_num_max) );
    	info.addNameStr("race:");      info.addValueStr( getRaceStr(race_id) );
        info.addNameStr("deteriori:"); info.addValueStr( int2str(deterioration) );
    	info.addNameStr("condition:"); info.addValueStr( int2str(condition) + "/" + int2str(data_item.condition_max) );
        info.addNameStr("mass:");      info.addValueStr( int2str(data_item.mass) );
    	info.addNameStr("price:");     info.addValueStr( int2str(price) );

}

bool BaseEquipment::InsertModule(BaseModule* module)
{
	if (module->GetParentSubTypeId() == data_id.subtype_id)
	{
		if (modules_vec.size() < data_item.modules_num_max)
    		{
    			if (module->GetItemSlot() != NULL)
    			{
    				module->GetItemSlot()->RemoveItem();
    			}
    			module->SetItemSlot(NULL);
    			module->SetEquipmentOwner(this);
	       		modules_vec.push_back(module);                
                        
        		UpdateProperties();
        		item_slot->UpdateVehiclePropetries();

        		return true;
    		}
    	}

       	return false;   
} 

/* virtual */
void BaseEquipment::Render(const Box& box, const Vec2<float>& gui_offset, bool draw_text)
{    	
    	RenderKorpus(box);
    
    	for (unsigned int i=0; i<modules_vec.size(); i++)
    	{
        	Rect module_rect(box.GetCenter().x + (1.1 * GUI::INSERTED_MODULE_SIZE) * (i), 
        		         box.GetCenter().y + (1.1 * GUI::INSERTED_MODULE_SIZE),
        			 GUI::INSERTED_MODULE_SIZE, 
        			 GUI::INSERTED_MODULE_SIZE);
        	drawTexturedRect(modules_vec[i]->GetTextureOb(), module_rect, -1.0f);
    	}
    	
    	if (condition == 0)
	{
	    	drawQuad_inXYPlane(GuiTextureObCollector::Instance().slot_mark_reject, box);
	}
	if (GetLocked() == true)
	{
		int font_size = 12;	
		drawQuad_inXYPlane(GuiTextureObCollector::Instance().slot_mark_accept, box);

    		Vec2<float> pos(box.GetCenter().x - font_size/2 + gui_offset.x, box.GetCenter().y - font_size + gui_offset.y);
    		Screen::Instance().DrawText(int2str(locked_turns), font_size, pos);	
	}

	if (draw_text == true)
	{
    		if (data_id.subtype_id == ENTITY::ROCKET_EQUIPMENT_ID)
        	{
        		Vec2<float> pos(box.GetCenter().x - box.GetSize().x/2 + gui_offset.x, box.GetCenter().y + gui_offset.y);
        		Screen::Instance().DrawText(int2str(((RocketEquipment*)this)->GetAmmo()) + "/" + int2str(((RocketEquipment*)this)->GetAmmoMax()), 12, pos);
		}
	}
}


void BaseEquipment::SaveDataUniqueBaseEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueBaseEquipment()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}

void BaseEquipment::LoadDataUniqueBaseEquipment(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueBaseEquipment()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}

void BaseEquipment::ResolveDataUniqueBaseEquipment()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueBaseEquipment()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}
