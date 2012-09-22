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

#include "MacroTask.hpp"
#include "../common/myStr.hpp"

MacroTask::MacroTask(int scenario_type_id, BaseGameEntity* target, int reward, int expiriance)
:BaseTask(scenario_type_id, target, reward, expiriance)
{}		

MacroTask::~MacroTask()
{}

void MacroTask::SaveDataUniqueMacroTask(boost::property_tree::ptree& save_ptree, const std::string& root) const	
{
	//save_ptree.put(root+"target_pos.x",   target_pos.x);
}

void MacroTask::LoadDataUniqueMacroTask(const boost::property_tree::ptree& load_ptree)
{
	//target_pos.x   = load_ptree.get<float>("target_pos.x");
}

void MacroTask::ResolveDataUniqueMacroTask()
{
	//((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseGameEntity.starsystem_id))->Add(this, vec2f(data_unresolved_BaseGameEntity.center.x, data_unresolved_BaseGameEntity.center.y)); 
}		

/*virtual*/
void MacroTask::SaveData(boost::property_tree::ptree& save_ptree, const std::string& parent_root) const
{
	const std::string root = parent_root + "macrotask.";
        //SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseTask(save_ptree, root);
	SaveDataUniqueMacroTask(save_ptree, root);
}

/*virtual*/		
void MacroTask::LoadData(const boost::property_tree::ptree& load_ptree)
{
        //LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseTask(load_ptree);
	LoadDataUniqueMacroTask(load_ptree);
}
	
/*virtual*/	
void MacroTask::ResolveData()
{
        //ResolveDataUniqueBase();
	ResolveDataUniqueBaseTask();
	ResolveDataUniqueMacroTask();
}





