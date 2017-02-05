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


#include "Skills.hpp"
#include "../common/constants.hpp"
#include "../common/common.hpp"

Skills::Skills()
    :
      m_attack(SKILLS::ATTACK_MIN),
      m_defence(SKILLS::DEFENCE_MIN),
      m_leader(SKILLS::LEADER_MIN),
      m_trader(SKILLS::TRADER_MIN),
      m_technic(SKILLS::TECHNIC_MIN),
      m_diplomat(SKILLS::DIPLOMAT_MIN),
      m_availablePoints(0),
      m_level(1),
      m_expirience(0),
      m_nextlevelExpirience(SKILLS::EXPIRIENCE_THRESHOLD)
{}     

Skills::~Skills() 
{}

void Skills::bindStrategy(const int* strategy)
{
    for (int i=0; i<SKILLS_NUM; i++)
    {
        this->m_strategy[i] = strategy[i];
    }
}

void Skills::addExpirience(unsigned long int addExpirience)
{
    m_expirience += addExpirience;
    while(__checkLevelUp() == true)
    {}
}

bool Skills::__checkLevelUp()
{
    if (m_expirience > m_nextlevelExpirience)
    {
        m_availablePoints += 1;
        m_nextlevelExpirience *= 2;
        m_level++;

        return true;
    }

    return false;
}

//######### ATTACK ###############
bool Skills::incrementAttack()
{
    if (m_availablePoints > 0)
    {
        m_availablePoints -= 1;
        m_attack += 1;
        return true;
    }
    
    return false;
}

void Skills::decrementAttack()
{
    m_availablePoints += 1;
    m_attack -= 1;
}


//######### DEFENCE ###############
bool Skills::IncrementDefence()
{
    if (m_availablePoints > 0)
    {
        m_availablePoints -= 1;
        m_defence += 1;
        return true;
    }
    
    return false;
} 

void Skills::DecrementDefence()
{
    m_availablePoints += 1;
    m_defence -= 1;
}


//######### LEADER ###############
bool Skills::IncrementLeader()
{
    if (m_availablePoints > 0) {
        m_availablePoints -= 1;
        m_leader += 1;
        return true;
    }
    
    return false;
}

void Skills::DecrementLeader()
{
    m_availablePoints += 1;
    m_leader -= 1;
}


//######### TRADER ###############
bool Skills::IncrementTrader()
{
    if (m_availablePoints > 0)
    {
        m_availablePoints -= 1;
        m_trader += 1;
        return true;
    }
    
    return false;
}

void Skills::DecrementTrader()
{
    m_availablePoints += 1;
    m_trader -= 1;
}

//######### TECHNIC ###############
bool Skills::IncrementTechnic()
{
    if (m_availablePoints > 0)
    {
        m_availablePoints -= 1;
        m_technic += 1;
        return true;
    }
    
    return false;
}

void Skills::DecrementTechnic()
{
    m_availablePoints += 1;
    m_technic -= 1;
}


//######### DIMPLOMAT ###############
bool Skills::IncrementDiplomat()
{
    if (m_availablePoints > 0)
    {
        m_availablePoints -= 1;
        m_diplomat += 1;
        return true;
    }
    
    return false;
}

void Skills::DecrementDiplomat()
{
    m_availablePoints += 1;
    m_diplomat -= 1;
}

void Skills::Save(boost::property_tree::ptree& save_ptree, const std::string& parent_root) const
{       
    const std::string root = parent_root+"skill.";
    save_ptree.put(root+"attack", m_attack);
    save_ptree.put(root+"defence", m_defence);
    save_ptree.put(root+"leader", m_leader);
    save_ptree.put(root+"trader", m_trader);
    save_ptree.put(root+"technic", m_technic);
    save_ptree.put(root+"diplomat", m_diplomat);
    save_ptree.put(root+"available_points", m_availablePoints);

    save_ptree.put(root+"expirience", m_expirience);
    save_ptree.put(root+"expirience_nextlevel", m_nextlevelExpirience);
}    

void Skills::Load(const boost::property_tree::ptree& load_ptree)
{
    m_attack = load_ptree.get<int>("attack");
    m_defence = load_ptree.get<int>("defence");
    m_leader = load_ptree.get<int>("leader");
    m_trader = load_ptree.get<int>("trader");
    m_technic = load_ptree.get<int>("technic");
    m_diplomat = load_ptree.get<int>("diplomat");
    m_availablePoints = load_ptree.get<int>("available_points");

    m_expirience = load_ptree.get<int>("expirience");
    m_nextlevelExpirience = load_ptree.get<int>("expirience_nextlevel");
}

void Skills::Resolve()
{}

void Skills::manageAccordingToStrategy()
{
    float strategy_norm[SKILLS_NUM] = {1.,1.,1.,1.,1.,1.};
    for (int i=0; i<SKILLS_NUM; i++)
    {
        strategy_norm[i] = (float)__skillDependingOnArrayIndex(i) / m_strategy[i];
    }
    
    int index_min = getIndexWithMinVal(strategy_norm, SKILLS_NUM);
    __incrementSkillDependingOnArrayIndex(index_min);

}

void Skills::__incrementSkillDependingOnArrayIndex(int i)
{
    switch(i)
    {
    case 0: { incrementAttack();   break; }
    case 1: { IncrementDefence();  break; }
    case 2: { IncrementLeader();   break; }
    case 3: { IncrementTrader();   break; }
    case 4: { IncrementTechnic();  break; }
    case 5: { IncrementDiplomat(); break; }
    }
}   

int Skills::__skillDependingOnArrayIndex(int i)
{
    switch(i)
    {
    case 0: { return m_attack; break; }
    case 1: { return m_defence; break; }
    case 2: { return m_leader; break; }
    case 3: { return m_trader; break; }
    case 4: { return m_technic; break; }
    case 5: { return m_diplomat; break; }
    }

    return 0;
}   

const int* getArrayDependingOnClassTypeId(entity::type class_type_id)
{
    switch(class_type_id)
    {
    case entity::type::WARRIOR_ID:   { return SKILLS_STRATEGY_WARRIOR; break; }
    case entity::type::PIRAT_ID:     { return SKILLS_STRATEGY_PIRAT; break; }
    case entity::type::TRADER_ID:    { return SKILLS_STRATEGY_TRADER; break; }
    case entity::type::DIPLOMAT_ID:  { return SKILLS_STRATEGY_DIPLOMAT; break; }
    }

    return nullptr;
}

const int* getArrayDependingOnRaceId(race::type race_id)
{
    switch(race_id)
    {
    case race::type::R0_ID: { return SKILLS_STRATEGY_RACE0; break; }
    case race::type::R1_ID: { return SKILLS_STRATEGY_RACE1; break; }
    case race::type::R2_ID: { return SKILLS_STRATEGY_RACE2; break; }
    case race::type::R3_ID: { return SKILLS_STRATEGY_RACE3; break; }
    case race::type::R4_ID: { return SKILLS_STRATEGY_RACE4; break; }
    case race::type::R6_ID: { return SKILLS_STRATEGY_RACE6; break; }
    case race::type::R7_ID: { return SKILLS_STRATEGY_RACE7; break; }
    }
    
    return nullptr;
}
