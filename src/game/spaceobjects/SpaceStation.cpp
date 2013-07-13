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

#include "SpaceStation.hpp"
#include "../common/rand.hpp"
#include "../common/myStr.hpp"
#include "../common/Logger.hpp"
#include "../world/EntityManager.hpp"

#include "../garbage/EntityGarbage.hpp"

#include "../world/starsystem.hpp"
#include "../docking/Kosmoport.hpp"
#include "../effects/Shield.hpp"
#include "../parts/WeaponComplex.hpp"
#include "../common/constants.hpp"
#include "../slots/ItemSlot.hpp"
#include "../pilots/Npc.hpp"

#include "../resources/ShaderCollector.hpp"
#include "../render/Render.hpp"

SpaceStation::SpaceStation(int id): land(nullptr)
{      
	data_id.id         = id;
	data_id.type_id    = ENTITY::eTYPE::VEHICLE_ID;
	data_id.subtype_id = ENTITY::eTYPE::SPACESTATION_ID;  
}

/* virtual */
SpaceStation::~SpaceStation() 
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~SpaceStation("+int2str(GetId())+")");
	#endif
}    
 
/* virtual */
void SpaceStation::PutChildsToGarbage() const
{
	for(unsigned int i=0; i<slot_total_vec.size(); i++)
	{
		EntityGarbage::Instance().Add(slot_total_vec[i]);	
	}	
	
	EntityGarbage::Instance().Add(land);
}

void SpaceStation::BindLand(BaseLand* land)       		
{
	this->land = land;
	this->land->SetOwner(this);
}
       	
void SpaceStation::UpdateInSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
	if (time > 0)
	{
		weapon_complex.Fire(time, owner_npc->GetSkills().GetAttackNormalized(), show_effect);
	}
}

//overriding
void SpaceStation::UpdateInfo()
{
	info.clear();

    info.addTitleStr("StarBase" + getEntityTypeStr(data_id.subtype_id));

    info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    info.addNameStr("mass:");        info.addValueStr(int2str(mass));
    info.addNameStr("pos:");       	 info.addValueStr( str(GetCenter()) );
} 

void SpaceStation::UpdateRenderStuff_2D()
{
    	//points.update(); 
    	protection_complex.GetShieldEffect()->Update();
    	
    	//if (ableTo.DRIVE == true)
    	//{
       		//drive_trail->update();
    	//}
}

void SpaceStation::RenderInSpace_2D()
{     
	UpdateRenderStuff_2D();
		
    	RenderKorpus();
    	
    	if (data_korpus.draw_turrels == true)
    	{
        	weapon_complex.RenderTurrels();
        }
    	
    	if (protection_complex.GetProtectorSlot()->GetItem() != nullptr)
    	{
        	RenderShieldEffect(1.0 - color.a); 
        }
        	
        starsystem->RestoreSceneColor();
}

				 		
void SpaceStation::RenderInSpace_3D(const Vec2<float>& scroll_coords)
{     	
	UpdateRenderAnimation();	
	RenderMeshLight(scroll_coords, starsystem->GetColor4f());        
}

void SpaceStation::SaveDataUniqueSpaceStation(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SpaceStation("+int2str(GetId())+")::SaveDataUniqueSpaceStation", SAVELOAD_LOG_DIP);
	#endif
}

void SpaceStation::LoadDataUniqueSpaceStation(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SpaceStation("+int2str(GetId())+")::LoadDataUniqueSpaceStation", SAVELOAD_LOG_DIP);
	#endif
}

void SpaceStation::ResolveDataUniqueSpaceStation()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SpaceStation("+int2str(GetId())+")::ResolveDataUniqueSpaceStation", SAVELOAD_LOG_DIP);
	#endif
}


/*virtual*/
void SpaceStation::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "spacestation."+int2str(data_id.id)+".";
        SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueOrientation(save_ptree, root);
	SaveDataUniqueBaseDrawable(save_ptree, root);
	SaveDataUniqueBaseSpaceEntity(save_ptree, root);
	SaveDataUniqueVehicle(save_ptree, root);
	SaveDataUniqueSpaceStation(save_ptree, root);
}

/*virtual*/
void SpaceStation::LoadData(const boost::property_tree::ptree& load_ptree)
{
        LoadDataUniqueBase(load_ptree);
        LoadDataUniqueOrientation(load_ptree);
	LoadDataUniqueBaseDrawable(load_ptree);
	LoadDataUniqueBaseSpaceEntity(load_ptree);
	LoadDataUniqueVehicle(load_ptree);
	LoadDataUniqueSpaceStation(load_ptree);
}

/*virtual*/
void SpaceStation::ResolveData()
{
        ResolveDataUniqueBase();
        ResolveDataUniqueOrientation();
	ResolveDataUniqueBaseDrawable();
	ResolveDataUniqueBaseSpaceEntity();
	ResolveDataUniqueVehicle();
	ResolveDataUniqueSpaceStation();
}
