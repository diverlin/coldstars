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
#include "../common/Global.hpp"
        
void Task::reset()
{
    m_scenario_type_id = ai::type::NONE;
    m_target_id = NONE;
    m_reward = 0;
    m_expiriance = 0;
}

void Task::save(boost::property_tree::ptree& save_ptree, const std::string& root) const    
{
    save_ptree.put(root+"result",     m_result);
    save_ptree.put(root+"reward",     m_reward);
    save_ptree.put(root+"expiriance", m_expiriance);
    save_ptree.put(root+"scenario_type_id", (int)m_scenario_type_id);
    save_ptree.put(root+"target_id", m_target_id);    
}

void Task::load(const boost::property_tree::ptree& load_ptree)
{
//    m_result     = load_ptree.get<int>("result");
//    m_reward     = load_ptree.get<int>("reward");
//    m_expiriance = load_ptree.get<int>("expiriance");
//    m_scenario_type_id = (ai::type)load_ptree.get<int>("scenario_type_id");
//    m_target_id = load_ptree.get<int>("target_id");
}

