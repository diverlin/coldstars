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
#include "../world/EntityManager.hpp"
#include "../slots/ItemSlot.hpp"
#include "../render/Render.hpp"
#include "../resources/TextureManager.hpp"
#include "../common/Logger.hpp"
#include "../common/myStr.hpp"

BaseItem::BaseItem()
{
        item_slot = nullptr;
        
        parent_subtype_id = NONE_ID;
        race_id = NONE_ID;
        
        condition = 0;
        price = 0;
        
        locked_turns = 0;
        
        textureOb = nullptr;
}

/* virtual */
BaseItem::~BaseItem()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~BaseItem("+int2str(GetId())+")");
	#endif
}

void BaseItem::LockEvent(int locked_turns)
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("BaseItem::LockEvent", ITEMINFLUENCE_LOG_DIP);
	#endif
	
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
                
void BaseItem::UseNormalDeterioration()
{
        deterioration =  data_item.deterioration_normal;
}
                                
void BaseItem::UseOverloadDeterioration()
{
        deterioration = data_item.deterioration_normal * data_item.deterioration_overload_rate;
}
 
void BaseItem::DamageEvent()
{
	#if ITEMINFLUENCE_LOG_ENABLED == 1
	Logger::Instance().Log("BaseItem::DamageEvent", ITEMINFLUENCE_LOG_DIP);
	#endif

        item_slot->UpdateVehiclePropetries();
}
                
void BaseItem::DeteriorationEvent()
{
        condition -= deterioration;
        if (condition <= 0)
    	{
    	        condition = 0;
        	DamageEvent();
	}
}         
                
bool BaseItem::RepairEvent()
{
    	condition = data_item.condition_max;
      	item_slot->UpdateVehiclePropetries();  
        
        return true;
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

void BaseItem::RenderInfo(const Vec2<float>& pos, float offset_x, float offset_y)
{  
	UpdateInfo();
	Vec2<float> pos2(pos.x - offset_x, pos.y - offset_y);
     	drawInfoIn2Column(info.title_list, info.value_list, pos2);
}

/* virtual */
void BaseItem::Render(const Box& box, const Vec2<float>& gui_offset, bool draw_text)
{
	RenderKorpus(box);
}

void BaseItem::RenderKorpus(const Box& box)
{
	if (Is3D())
	{
		disable_BLEND();
		Vec3<float> v(0.0);
		Color4<float> c(1.0, 1.0, 1.0, 1.0);
		SetCenter(box.GetCenter());
		//SetAngle(box.GetAngle());
		UpdateRenderAnimation();
		//SetScale(box.GetSize());
		RenderMeshLight(v, c);
		enable_BLEND();
	}
	else
	{
       		drawQuad_inXYPlane(textureOb, box); 
	}
}

void BaseItem::SaveDataUniqueBaseItem(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueBaseItem()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
        save_ptree.put(root+"price", price);
        save_ptree.put(root+"condition", condition);
        save_ptree.put(root+"locked_turns", locked_turns);
        save_ptree.put(root+"race_id", race_id);
        save_ptree.put(root+"parent_subtype_id", parent_subtype_id);

        save_ptree.put(root+"data_item.tech_level",    data_item.tech_level);        
        save_ptree.put(root+"data_item.modules_num_max",    data_item.modules_num_max);
        save_ptree.put(root+"data_item.condition_max",      data_item.condition_max);                         
        save_ptree.put(root+"data_item.deterioration_normal", data_item.deterioration_normal);   
        save_ptree.put(root+"data_item.deterioration_overload_rate", data_item.deterioration_overload_rate);   
        save_ptree.put(root+"data_item.mass",               data_item.mass);
                    
	if (textureOb) 	save_ptree.put(root+"unresolved.textureOb_path", textureOb->path);
	else            save_ptree.put(root+"unresolved.textureOb_path", "none");
        
        if (item_slot) 	{ save_ptree.put(root+"unresolved.item_slot_id", item_slot->GetId()); }
	else           	{ save_ptree.put(root+"unresolved.item_slot_id", NONE_ID); }
}

void BaseItem::LoadDataUniqueBaseItem(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueBaseItem()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
        price             = load_ptree.get<int>("price");
        condition         = load_ptree.get<int>("condition");
        locked_turns      = load_ptree.get<int>("locked_turns");
        race_id           = load_ptree.get<int>("race_id");
        parent_subtype_id = load_ptree.get<int>("parent_subtype_id");

        data_item.tech_level           = load_ptree.get<int>("data_item.tech_level");    
        data_item.modules_num_max      = load_ptree.get<int>("data_item.modules_num_max");
        data_item.condition_max        = load_ptree.get<int>("data_item.condition_max");                         
        data_item.deterioration_normal = load_ptree.get<int>("data_item.deterioration_normal");   
        data_item.deterioration_overload_rate = load_ptree.get<float>("data_item.deterioration_overload_rate");   
        data_item.mass                 = load_ptree.get<int>("data_item.mass");
                    
	data_unresolved_BaseItem.textureOb_path = load_ptree.get<std::string>("unresolved.textureOb_path");
	data_unresolved_BaseItem.item_slot_id   = load_ptree.get<int>("unresolved.item_slot_id");
}
                
void BaseItem::ResolveDataUniqueBaseItem()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueBaseItem()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	textureOb = TextureManager::Instance().GetTextureObByPath(data_unresolved_BaseItem.textureOb_path);
	
	UseNormalDeterioration();	
	UpdateProperties(); // this function must be performed before inserting to slot!!!
		
	if(data_unresolved_BaseItem.item_slot_id != NONE_ID) // item_slot can be nullptr in case of inserted module
	{
		((ItemSlot*)EntityManager::Instance().GetEntityById(data_unresolved_BaseItem.item_slot_id))->InsertItem(this);
	}
}
