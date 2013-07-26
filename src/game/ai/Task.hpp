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

#ifndef TASK_HPP
#define TASK_HPP

#include <boost/property_tree/ptree.hpp>
#include <common/constants.hpp>
#include <types/MyInt.hpp>
#include <common/AiScenarioTypes.hpp>

class Task
{
	public:
		Task(TYPE::AISCENARIO scenario_type_id = TYPE::AISCENARIO::NONE_ID, INTLONGEST target_id = NONE_ID, int reward = 0, int expiriance = 0):
		result(NONE_ID),
		reward(reward),
		expiriance(expiriance),
		scenario_type_id(scenario_type_id),
		target_id(target_id)
		{}
		
		~Task() {};

		void SetResult(int result)  { this->result = result; }
				
		TYPE::AISCENARIO GetScenarioTypeId() const { return scenario_type_id; };
		INTLONGEST GetTargetId() const { return target_id; };
				
		int GetResult() const { return result; };
		
		void Reset();
				
		void SaveData(boost::property_tree::ptree&, const std::string&) const;
		void LoadData(const boost::property_tree::ptree&);
				
	protected:
		int result;
	
		int reward;
		int expiriance;
		
		TYPE::AISCENARIO scenario_type_id;
		INTLONGEST target_id;	
};

#endif 
     
