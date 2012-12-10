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
#include "../common/EntityManager.hpp"
#include "../world/starsystem.hpp"
#include "../render/Render.hpp"
#include "../effects/particlesystem/ExplosionEffect.hpp"

#include "../garbage/EntityGarbage.hpp"

Container::Container(int id)
{
	data_id.id         = id;
	data_id.type_id    = ENTITY::CONTAINER_ID;
        data_id.subtype_id = NONE_ID;
	
    	mass = 1;

   	item_slot = NULL;
    	
    	velocity = getRandInt(40, 42) / 100.0;
}

/* virtual */   
Container::~Container()
{}

void Container::PutChildsToGarbage() const
{
	item_slot->PutChildsToGarbage();
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
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
}        
       	
void Container::RenderInfoInSpace(const vec2f& scroll_coords)
{
	UpdateInfo();
     	drawInfoIn2Column(info.title_list, info.value_list, points.GetCenter().x - scroll_coords.x - 200, points.GetCenter().y - scroll_coords.y);
     	item_slot->GetItem()->RenderInfo(points.GetCenter(), scroll_coords.x, scroll_coords.y);
}
 
/* virtual */    
void Container::PostDeathUniqueEvent(bool show_effect)
{
        if (item_slot->GetItem()->GetTypeId() == ENTITY::BOMB_ID)
        {
        	starsystem->BombExplosionEvent(this, show_effect);  
        }
        else
        {
        	if (show_effect == true)
        	{
        		createExplosion(starsystem, points.GetCenter(), textureOb->size_id);  
        	}
        }
}

void Container::CalcCollisionrRadius()
{
        collision_radius = (textureOb->GetFrameWidth() + textureOb->GetFrameHeight())/4; 
        
        points.SetWidthHeight(textureOb->GetFrameWidth(), textureOb->GetFrameHeight());  // needs for finding visible corners
}

void Container::UpdateInSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
	UpdateRotation();
		
	if (time > 0)
	{
     		if (fabs(velocity) > 0.2f)
     		{
			velocity -= 0.1f;
        		get_dPos_ToPoint(points.GetCenter(), target_pos, velocity, d_pos);

     		}  
     		else
     		{
     			d_pos.Set(0.0f, 0.0f);
     		}

		points.SetCenter(points.GetCenter().x + d_pos.x, points.GetCenter().y + d_pos.y);
     	}
}
       		
void Container::Render2D()
{ 
    	drawDynamic(textureOb, points.GetCenter(), angle.z, points.GetPosZ());
}

void Container::SaveDataUniqueContainer(boost::property_tree::ptree& save_ptree, const std::string& root) const	
{
	save_ptree.put(root+"target_pos.x", target_pos.x);
	save_ptree.put(root+"target_pos.y", target_pos.y);

	save_ptree.put(root+"velocity", velocity);
}

void Container::LoadDataUniqueContainer(const boost::property_tree::ptree& load_ptree)
{
	target_pos.x   = load_ptree.get<float>("target_pos.x");
	target_pos.y   = load_ptree.get<float>("target_pos.y");
	
	velocity = load_ptree.get<float>("velocity");
}

void Container::ResolveDataUniqueContainer()
{
	((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->AddContainer(this, vec2f(data_unresolved_BaseSpaceEntity.center.x, data_unresolved_BaseSpaceEntity.center.y)); 
}		

/*virtual*/
void Container::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "container." + int2str(GetId()) + ".";
        SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseSpaceEntity(save_ptree, root);
	SaveDataUniqueContainer(save_ptree, root);
}

/*virtual*/		
void Container::LoadData(const boost::property_tree::ptree& load_ptree)
{
        LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseSpaceEntity(load_ptree);
	LoadDataUniqueContainer(load_ptree);
}
	
/*virtual*/	
void Container::ResolveData()
{
        ResolveDataUniqueBase();
	ResolveDataUniqueBaseSpaceEntity();
	ResolveDataUniqueContainer();
}
