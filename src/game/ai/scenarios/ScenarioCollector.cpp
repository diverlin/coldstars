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

#include "ScenarioCollector.hpp"

ScenarioCollector& ScenarioCollector::Instance()
{
    static ScenarioCollector instance;
    return instance;
}

ScenarioCollector::~ScenarioCollector()
{}

void ScenarioCollector::RegisterScenario(BaseScenario* scenario)
{
    scenario_map.insert(std::make_pair(scenario->GetTypeId(), scenario));
}
          
BaseScenario* ScenarioCollector::GetScenario(TYPE::AISCENARIO type_id) const
{
    if (type_id != TYPE::AISCENARIO::NONE_ID)
    {
        return (scenario_map.find(type_id))->second;
    }
    return nullptr;
}
