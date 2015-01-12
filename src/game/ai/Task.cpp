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

#include "Task.hpp"
#include "../spaceobjects/SpaceObject.hpp"
#include "../world/EntityManager.hpp"
        
void Task::Reset()
{
    scenario_type_id = TYPE::AISCENARIO::NONE_ID;
    target_id = NONE_ID;
    reward = 0;
    expiriance = 0;
}

void Task::Save(boost::property_tree::ptree& save_ptree, const std::string& root) const    
{
    save_ptree.put(root+"result",     result);
    save_ptree.put(root+"reward",     reward);
    save_ptree.put(root+"expiriance", expiriance);
    save_ptree.put(root+"scenario_type_id", (int)scenario_type_id);
    save_ptree.put(root+"target_id", target_id);    
}

void Task::Load(const boost::property_tree::ptree& load_ptree)
{
    result     = load_ptree.get<int>("result");
    reward     = load_ptree.get<int>("reward");
    expiriance = load_ptree.get<int>("expiriance");
    scenario_type_id = (TYPE::AISCENARIO)load_ptree.get<int>("scenario_type_id");    
    target_id = load_ptree.get<int>("target_id");
}

