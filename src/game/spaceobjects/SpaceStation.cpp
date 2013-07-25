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

SpaceStation::SpaceStation(int id)
: 
land(nullptr)
{      
	SetId(id);
	SetTypeId(ENTITY::TYPE::VEHICLE_ID);
	SetSubTypeId(ENTITY::TYPE::SPACESTATION_ID);
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
		GetComplexWeapon().Fire(time, GetOwnerNpc()->GetSkills().GetAttackNormalized(), show_effect);
	}
}

//overriding
void SpaceStation::UpdateInfo()
{
	GetInfo().clear();

    GetInfo().addTitleStr("StarBase" + getEntityTypeStr(GetSubTypeId()));

    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(int2str(GetId()) + " / " + int2str(GetStarSystem()->GetId()));
    GetInfo().addNameStr("id:");          GetInfo().addValueStr(int2str(GetId()));
    GetInfo().addNameStr("mass:");        GetInfo().addValueStr(int2str(GetMass()));
    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(GetCenter()) );
} 

void SpaceStation::UpdateRenderStuff_2D()
{
    //points.update(); 
    GetComplexProtector().GetShieldEffect()->Update();
    
    //if (ableTo.DRIVE == true)
    //{
        //drive_trail->update();
    //}
}

void SpaceStation::RenderInSpace_2D(float scale)
{     
	UpdateRenderStuff_2D();
		
    RenderKorpus();
    	
    if (GetDataKorpus().draw_turrels == true)
    {
        GetComplexWeapon().RenderTurrels();
    }
    
    if (GetComplexProtector().GetProtectorSlot()->GetItem() != nullptr)
    {
        RenderShieldEffect(1.0 - GetColor().a); 
    }
        
    GetStarSystem()->RestoreSceneColor();
}

				 		
void SpaceStation::RenderInSpace_3D(const Vec2<float>& scroll_coords, float scale)
{     	
	UpdateRenderAnimation();	
	RenderMeshLight(scroll_coords, GetStarSystem()->GetColor4f());        
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
    const std::string root = "spacestation."+int2str(GetId())+".";
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
