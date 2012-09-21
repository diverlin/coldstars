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

#include "MicroTask.hpp"
#include "../common/myStr.hpp"

MicroTask::MicroTask(int scenario_type_id, BaseGameEntity* target, int reward, int expiriance)
:BaseTask(scenario_type_id, target, reward, expiriance)
{}		

MicroTask::~MicroTask()
{}


void MicroTask::SaveDataUniqueMicroTask(boost::property_tree::ptree& save_ptree, const std::string& root) const	
{
	//save_ptree.put(root+"target_pos.x",   target_pos.x);
}

void MicroTask::LoadDataUniqueMicroTask(const boost::property_tree::ptree& load_ptree)
{
	//target_pos.x   = load_ptree.get<float>("target_pos.x");
}

void MicroTask::ResolveDataUniqueMicroTask()
{
	//((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseGameEntity.starsystem_id))->Add(this, vec2f(data_unresolved_BaseGameEntity.center.x, data_unresolved_BaseGameEntity.center.y)); 
}		

/*virtual*/
void MicroTask::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "microtask.";
        //SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseTask(save_ptree, root);
	SaveDataUniqueMicroTask(save_ptree, root);
}

/*virtual*/		
void MicroTask::LoadData(const boost::property_tree::ptree& load_ptree)
{
        //LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseTask(load_ptree);
	LoadDataUniqueMicroTask(load_ptree);
}
	
/*virtual*/	
void MicroTask::ResolveData()
{
        //ResolveDataUniqueBase();
	ResolveDataUniqueBaseTask();
	ResolveDataUniqueMicroTask();
}



