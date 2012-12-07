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

#include "Satellite.hpp"
#include "../common/rand.hpp"
#include "../common/myStr.hpp"
#include "../common/Logger.hpp"
#include "../common/EntityManager.hpp"
#include "../world/starsystem.hpp"
#include "../effects/Shield.hpp"
#include "../slots/ItemSlot.hpp"
#include "../parts/WeaponComplex.hpp"
#include "../pilots/Npc.hpp"

Satellite::Satellite(int id)
{        
	data_id.id = id;
	data_id.type_id = ENTITY::VEHICLE_ID;
	data_id.subtype_id = ENTITY::SATELLITE_ID;
	
    	mass = getRandInt(ENTITY::SATELLITE::MASS_MIN, ENTITY::SATELLITE::MASS_MAX);
    	orbit = new Orbit();
    	
    	d_angle.z = 1.0f;
}

/* virtual */
Satellite::~Satellite() 
{
	delete orbit;
}

void Satellite::UpdateInSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
	if (time > 0)
	{
		orbit->UpdatePosition();

		//printf("sat orbit =%f,%f\n", orbit->getPosition().x, orbit->getPosition().y);
		//if (parent != NULL)
		//{		
			vec2f new_pos;
			new_pos.x = parent->GetPoints().GetCenter().x + orbit->GetPosition().x;
			new_pos.y = parent->GetPoints().GetCenter().y + orbit->GetPosition().y;
			points.SetCenter(new_pos);
			points.Update();
		//}
		//else
		//{
			//points.SetCenter(orbit->getPosition());
		//}
		
		weapon_complex.Fire(time, owner_npc->GetSkill().GetAttack(), show_effect);
	}
}

void Satellite::UpdateInfo()
{
	info.clear();

    	info.addTitleStr("SATELLITE");

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            
void Satellite::UpdateRenderStuff()
{
    	//points.update(); 
    	protection_complex.GetShieldEffect()->Update();
    	
    	this->UpdateRotation();
	points.SetAngle(angle.z);
    	//printf("3. angle = %f\n", angle.z);
    	points.Update();
    		
    	//if (ableTo.DRIVE == true)
    	//{
       		//drive_trail->update();
    	//}
}

void Satellite::RenderInSpace() const
{   
        //if (ableTo.GRAB == true)
        //{
                //renderGrappleTrail();
        //}
        
    	RenderKorpus();
    	
    	if (data_korpus.draw_turrels == true)
    	{
        	weapon_complex.RenderTurrels();
        }

    	//if (ableTo.DRIVE == true)
    	//{
		//renderDriveTrail();
    	//}
    	
        if (protection_complex.GetProtectorSlot()->GetItem() != NULL)
    	{
        	RenderShieldEffect(1.0 - color.a); 
        }
}

void Satellite::RenderAtPlanet() const
{
	RenderKorpus();
	
	if (data_korpus.draw_turrels == true)
    	{
        	weapon_complex.RenderTurrels();
        }
}		




/*virtual*/
void Satellite::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "satellite."+int2str(data_id.id)+".";
        SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseSpaceEntity(save_ptree, root);
	SaveDataUniqueVehicle(save_ptree, root);
	SaveDataUniqueSatellite(save_ptree, root);
}

/*virtual*/
void Satellite::LoadData(const boost::property_tree::ptree& load_ptree)
{
        LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseSpaceEntity(load_ptree);
	LoadDataUniqueVehicle(load_ptree);
	LoadDataUniqueSatellite(load_ptree);
}

/*virtual*/
void Satellite::ResolveData()
{
        ResolveDataUniqueBase();
	ResolveDataUniqueBaseSpaceEntity();
	ResolveDataUniqueVehicle();
	ResolveDataUniqueSatellite();
}

void Satellite::SaveDataUniqueSatellite(boost::property_tree::ptree&, const std::string&) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueSatellite()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}

void Satellite::LoadDataUniqueSatellite(const boost::property_tree::ptree&)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueSatellite()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}

void Satellite::ResolveDataUniqueSatellite()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueSatellite()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}



