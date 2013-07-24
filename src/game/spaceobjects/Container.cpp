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

#include "Container.hpp"
#include "../items/BaseItem.hpp"
#include "../common/common.hpp"
#include "../common/constants.hpp"

#include "../common/rand.hpp"
#include "../common/myStr.hpp"
#include "../world/EntityManager.hpp"
#include "../world/starsystem.hpp"
#include "../render/Render.hpp"
#include "../render/Screen.hpp"
#include "../effects/particlesystem/ExplosionEffect.hpp"

#include "../garbage/EntityGarbage.hpp"
#include "../common/Logger.hpp"

Container::Container(int id)
:
item_slot(nullptr)    
{
	SetId(id);
	SetTypeId(ENTITY::TYPE::VEHICLE_ID);
	SetSubTypeId(ENTITY::TYPE::CONTAINER_ID);
	
	velocity = getRandInt(40, 42) / 100.0;
}

/* virtual */   
Container::~Container()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~Container("+int2str(GetId())+")");
	#endif
}

/* virtual */
void Container::PutChildsToGarbage() const
{
	EntityGarbage::Instance().Add(item_slot);
}
        	
void Container::BindItemSlot(ItemSlot* item_slot) 
{ 
	this->item_slot = item_slot; 
	item_slot->SetOwner(this); 
}

void Container::UpdateInfo()  
{
	info.clear();
	info.addTitleStr("CONTAINER");
	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(GetId()) + " / " + int2str(starsystem->GetId()));
	info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
	info.addNameStr("pos:");       		info.addValueStr( str(GetCenter()) );
}        
 
/* virtual override final */       	
void Container::RenderInfoInSpace(const Vec2<float>& scroll_coords, float zoom)
{
	UpdateInfo();
	Vec2<float> pos(GetCenter().x - scroll_coords.x, GetCenter().y - scroll_coords.y);
    pos /= zoom;
	drawInfoIn2Column(info.title_list, info.value_list, pos);
    
    Vec2<float> pos2(pos.x + 200, pos.y);
	item_slot->GetItem()->RenderInfo(pos2);
}
 
/* virtual */    
void Container::PostDeathUniqueEvent(bool show_effect)
{
	if (item_slot->GetItem()->GetTypeId() == ENTITY::TYPE::BOMB_ID)
	{
		starsystem->BombExplosionEvent(this, show_effect);  
	}
	else
	{
		if (show_effect == true)
		{
			ExplosionEffect* explosion = getNewExplosionEffect(GetCollisionRadius());
			starsystem->Add(explosion, GetCenter()); 
		}
	}
}

void Container::UpdateInSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
		
	if (time > 0)
	{
		SetCenter(GetCenter() + force);
		force *= 0.99;
	}
}
       		
void Container::Render2D()
{ 
	UpdateRenderAnimation();
	drawQuad(textureOb, GetCenter(), GetSize(), GetAngle().z);
}

void Container::SaveDataUniqueContainer(boost::property_tree::ptree& save_ptree, const std::string& root) const	
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Container("+int2str(GetId())+")::SaveDataUniqueContainer", SAVELOAD_LOG_DIP);
	#endif
	
	save_ptree.put(root+"target_pos.x", target_pos.x);
	save_ptree.put(root+"target_pos.y", target_pos.y);

	save_ptree.put(root+"velocity", velocity);
}

void Container::LoadDataUniqueContainer(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Container("+int2str(GetId())+")::LoadDataUniqueContainer", SAVELOAD_LOG_DIP);
	#endif
	
	target_pos.x   = load_ptree.get<float>("target_pos.x");
	target_pos.y   = load_ptree.get<float>("target_pos.y");
	
	velocity = load_ptree.get<float>("velocity");
}

void Container::ResolveDataUniqueContainer()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Container("+int2str(GetId())+")::ResolveDataUniqueContainer", SAVELOAD_LOG_DIP);
	#endif
	
	((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->AddContainer(this, data_unresolved_Orientation.center); 
}		

/*virtual*/
void Container::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "container." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueOrientation(save_ptree, root);
	SaveDataUniqueBaseDrawable(save_ptree, root);
	SaveDataUniqueBaseSpaceEntity(save_ptree, root);
	SaveDataUniqueContainer(save_ptree, root);
}

/*virtual*/		
void Container::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueOrientation(load_ptree);
	LoadDataUniqueBaseDrawable(load_ptree);
	LoadDataUniqueBaseSpaceEntity(load_ptree);
	LoadDataUniqueContainer(load_ptree);
}
	
/*virtual*/	
void Container::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueOrientation();
	ResolveDataUniqueBaseDrawable();
	ResolveDataUniqueBaseSpaceEntity();
	ResolveDataUniqueContainer();
}
