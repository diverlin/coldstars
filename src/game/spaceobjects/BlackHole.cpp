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

#include "BlackHole.hpp"
#include "../resources/MeshCollector.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"
#include "../common/rand.hpp"
#include "../common/Logger.hpp"

#include "../common/IdGenerator.hpp"
#include "../resources/TextureManager.hpp"
#include "../world/starsystem.hpp"

BlackHole::BlackHole(int id)
{        
	data_id.id = id;
	data_id.type_id = ENTITY::BLACKHOLE_ID;
	
    	mass = getRandInt(1000, 4000);
}

/* virtual */
BlackHole::~BlackHole() 
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~BlackHole("+int2str(GetId())+")");
	#endif
	
	delete shockwave; 
} 
 
void BlackHole::SetCenter(const Vec2<float>& center) { points.SetCenter(center); shockwave->SetCenter(center); }
 		
void BlackHole::UpdateInSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);

	if (time > 0)
	{
		points.SetCenter(points.GetCenter()+getRandVec2f(1, 2));
		shockwave->SetCenter(points.GetCenter());
	
		data_life.life_time--;
		if (data_life.life_time < 0)
		{
			//scale -= 0.1;
			//if (scale < 1.0)
			{
				data_life.is_alive = false;
			}
		}
	}

	shockwave->Update();
}

void BlackHole::UpdateInfo()
{
	info.clear();

    	info.addTitleStr("BLACKHOLE");

    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
      
void BlackHole::Render_NEW(const Vec2<float>& scroll_coords)
{
	UpdateRenderAnimation();
	RenderMesh(scroll_coords, starsystem->GetColor4f());
}
	
void BlackHole::Render_OLD() const
{
	RenderMesh_OLD();	
}
     
void BlackHole::SaveDataUniqueBlackHole(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BlackHole("+int2str(GetId())+")::SaveDataUniqueBlackHole", SAVELOAD_LOG_DIP);
	#endif
}

void BlackHole::LoadDataUniqueBlackHole(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BlackHole("+int2str(GetId())+")::LoadDataUniqueBlackHole", SAVELOAD_LOG_DIP);
	#endif
}

void BlackHole::ResolveDataUniqueBlackHole()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BlackHole("+int2str(GetId())+")::ResolveDataUniqueBlackHole", SAVELOAD_LOG_DIP);
	#endif
	
	starsystem->Add(this, data_unresolved_Orientation.center); 
}
 
/*virtual*/
void BlackHole::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "blackhole." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueOrientation(save_ptree, root);
	SaveDataUniqueBaseDrawable(save_ptree, root);
	SaveDataUniqueBaseSpaceEntity(save_ptree, root);
	SaveDataUniqueBasePlanet(save_ptree, root);
	SaveDataUniqueBlackHole(save_ptree, root);
}

/*virtual*/		
void BlackHole::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueOrientation(load_ptree);
	LoadDataUniqueBaseDrawable(load_ptree);
	LoadDataUniqueBaseSpaceEntity(load_ptree);
	LoadDataUniqueBasePlanet(load_ptree);
	LoadDataUniqueBlackHole(load_ptree);
}
	
/*virtual*/	
void BlackHole::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueOrientation();
	ResolveDataUniqueBaseDrawable();
	ResolveDataUniqueBaseSpaceEntity();
	ResolveDataUniqueBasePlanet();
	ResolveDataUniqueBlackHole();
}
