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

#pragma once

#include <boost/property_tree/ptree.hpp>

#include <types/IdType.hpp>
#include <types/AiScenarioTypes.hpp>

class Task
{
    public:
        Task(TYPE::AISCENARIO scenario_type_id = TYPE::AISCENARIO::NONE_ID, IDTYPE target_id = NONE_ID, int reward = 0, int expiriance = 0):
        m_reward(reward),
        m_expiriance(expiriance),
        m_scenario_type_id(scenario_type_id),
        m_target_id(target_id)
        {}
        
        ~Task() {}

        void SetResult(int result)  { m_result = result; }
                
        TYPE::AISCENARIO GetScenarioTypeId() const { return m_scenario_type_id; }
        IDTYPE targetId() const { return m_target_id; }
                
        int result() const { return m_result; }
        
        void reset();
                
        void save(boost::property_tree::ptree&, const std::string&) const;
        void load(const boost::property_tree::ptree&);
                
    protected:
        int m_result = NONE_ID;
    
        int m_reward = 0;
        int m_expiriance = 0;
        
        TYPE::AISCENARIO m_scenario_type_id;
        IDTYPE m_target_id = 0;
};


     
