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


#include "Ship.hpp"

#include <boost/lexical_cast.hpp>

#include "../common/myStr.hpp"
#include "../world/EntityManager.hpp"

#include "../world/starsystem.hpp"

#include "../render/Render.hpp"
#include "../effects/Shield.hpp"
#include "../items/equipment/GrappleEquipment.hpp"
#include "../slots/ItemSlot.hpp"
#include "../slots/VehicleSlot.hpp"
#include "../parts/WeaponComplex.hpp"
#include "../common/Logger.hpp"

#include "../pilots/Npc.hpp"


Ship::Ship(int id)
{
	SetId(id);
	SetTypeId(ENTITY::TYPE::VEHICLE_ID);
	SetSubTypeId(ENTITY::TYPE::SHIP_ID);
}

/* virtual */
Ship::~Ship()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~Ship("+int2str(GetId())+")");
	#endif
} 


//overriding
void Ship::UpdateInfo()
{
	GetInfo().clear();

	GetInfo().addTitleStr("SHIP");
	if (GetStarSystem()) { GetInfo().addNameStr("id/ss_id:"); GetInfo().addValueStr( int2str(GetId()) + " / " + int2str(GetStarSystem()->GetId()) ); }
	else     		{ GetInfo().addNameStr("id:");       GetInfo().addValueStr( int2str(GetId()) ); }
	GetInfo().addNameStr("race:");   		GetInfo().addValueStr( getRaceStr(GetTextureOb()->race_id) ); 
	GetInfo().addNameStr("class:");   		GetInfo().addValueStr( getEntityTypeStr(GetSubSubTypeId()) );     	
	GetInfo().addNameStr("armor/max:");     GetInfo().addValueStr( int2str(GetDataLife().armor) + "/" + int2str(data_korpus.armor) );
	GetInfo().addNameStr("size id:");     	GetInfo().addValueStr( int2str(GetTextureOb()->size_id) );
	GetInfo().addNameStr("space/free:");   	GetInfo().addValueStr( int2str(data_korpus.space) + "/" + int2str(properties.free_space) );
	GetInfo().addNameStr("mass:");   		GetInfo().addValueStr( int2str(GetMass()) );
	GetInfo().addNameStr("speedx100:");     GetInfo().addValueStr( int2str(properties.speed*100) );
	GetInfo().addNameStr("speed dmx100:");  GetInfo().addValueStr( int2str(GetMass()*MASS_DECREASE_SPEED_RATE*100));
	GetInfo().addNameStr("energy:");        GetInfo().addValueStr( int2str(properties.energy) );
	GetInfo().addNameStr("temp.:");       	GetInfo().addValueStr( int2str(data_korpus.temperature) );
	GetInfo().addNameStr("radar:");    		GetInfo().addValueStr( int2str(properties.radar) );
	GetInfo().addNameStr("protect:");       GetInfo().addValueStr( int2str(properties.protection) );
	GetInfo().addNameStr("repair:");        GetInfo().addValueStr( int2str(properties.repair) );
	GetInfo().addNameStr("scan:");        	GetInfo().addValueStr( int2str(properties.scan) );
	GetInfo().addNameStr("price:");       	GetInfo().addValueStr( int2str(data_korpus.price) );
	GetInfo().addNameStr("pos:");       	GetInfo().addValueStr( str(GetCenter()) );
		
	if (properties.grab_radius > 0)
	{
		std::string grab_str = GetGrappleSlot()->GetGrappleEquipment()->GetTargetStr();
		if (grab_str.size() > 0)
		{
			GetInfo().addNameStr("grab_id:");   		GetInfo().addValueStr( grab_str ); 
		}
	}

	//info.addNameStr("attackR:");       	info.addValueStr( boost::lexical_cast<std::string>(propetries.attack_rate_normalized) );	
	//info.addNameStr("defenceR:");       	info.addValueStr( boost::lexical_cast<std::string>(propetries.defence_rate_normalized) );	
}

/* virtual */
void Ship::UpdateInSpace(int time, bool show_effect)
{   
	CheckDeath(show_effect);
	protection_complex.GetShieldEffect()->Update();
    		
	if (time > 0)
	{
		UpdateSpecialAction();
		
		owner_npc->UpdateInSpace(time, show_effect);
		UpdateOrientation();   
		weapon_complex.Fire(time, owner_npc->GetSkills().GetAttackNormalized(), show_effect);
		
		if (properties.speed > 0) 
		{ 
			drive_complex.UpdatePosition();
		}
		
		UpdateGrappleMicroProgram_inDynamic();
	}
}

void Ship::RenderInSpace_2D(float scale) const
{   
	setColor4f(color);
	if (properties.grab_radius > 0)
	{
		RenderGrabTrail();
	}
	
	RenderKorpus();
	
	if (data_korpus.draw_turrels == true)
	{
		weapon_complex.RenderTurrels();
	}
	
	if (properties.speed > 0)
	{
		RenderDriveEffect(scale , 1.0 - color.a);
	}
	
	if (properties.shield_effect_enabled == true)
	{
		RenderShieldEffect(1.0 - color.a); 
	}
	GetStarSystem()->RestoreSceneColor();
}

void Ship::RenderInSpace_3D(const Vec2<float>& scroll_coords, float scale)
{
	UpdateRenderAnimation();
	RenderMeshLight(scroll_coords, GetStarSystem()->GetColor4f());

	setColor4f(color);
	enable_BLEND();
	if (properties.shield_effect_enabled == true)
	{
		RenderShieldEffect(1.0 - color.a); 
	}
	disable_BLEND();
	GetStarSystem()->RestoreSceneColor();
}

void Ship::RenderAtPlanet(const Vec3<float>& center)
{
	SetCenter(center);
	SetAngleZ(0);
	UpdateOrientation();
	
	RenderKorpus();
	
	if (data_korpus.draw_turrels == true)
	{
		weapon_complex.RenderTurrels();
	}
}		

void Ship::SaveDataUniqueShip(boost::property_tree::ptree&, const std::string&) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Ship("+int2str(GetId())+")::SaveDataUniqueShip", SAVELOAD_LOG_DIP);
	#endif
}

void Ship::LoadDataUniqueShip(const boost::property_tree::ptree&)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Ship("+int2str(GetId())+")::LoadDataUniqueShip", SAVELOAD_LOG_DIP);
	#endif
}

void Ship::ResolveDataUniqueShip()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Ship("+int2str(GetId())+")::ResolveDataUniqueShip", SAVELOAD_LOG_DIP);
	#endif
}

/*virtual*/
void Ship::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "ship."+int2str(GetId())+".";
    SaveDataUniqueBase(save_ptree, root);
    SaveDataUniqueOrientation(save_ptree, root);
	SaveDataUniqueBaseDrawable(save_ptree, root);
	SaveDataUniqueBaseSpaceEntity(save_ptree, root);
	SaveDataUniqueVehicle(save_ptree, root);
	SaveDataUniqueShip(save_ptree, root);
}

/*virtual*/
void Ship::LoadData(const boost::property_tree::ptree& load_ptree)
{
        LoadDataUniqueBase(load_ptree);
        LoadDataUniqueOrientation(load_ptree);
	LoadDataUniqueBaseDrawable(load_ptree);
	LoadDataUniqueBaseSpaceEntity(load_ptree);
	LoadDataUniqueVehicle(load_ptree);
	LoadDataUniqueShip(load_ptree);
}

/*virtual*/
void Ship::ResolveData()
{
        ResolveDataUniqueBase();
        ResolveDataUniqueOrientation();
	ResolveDataUniqueBaseDrawable();
	ResolveDataUniqueBaseSpaceEntity();
	ResolveDataUniqueVehicle();
	ResolveDataUniqueShip();
}
