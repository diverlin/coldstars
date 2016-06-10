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
attack(SKILLS::ATTACK_MIN),
defence(SKILLS::DEFENCE_MIN),
leader(SKILLS::LEADER_MIN),
trader(SKILLS::TRADER_MIN),
technic(SKILLS::TECHNIC_MIN),
diplomat(SKILLS::DIPLOMAT_MIN),
available_points(0),
level(1),
expirience(0),
expirience_nextlevel(SKILLS::EXPIRIENCE_THRESHOLD)
{}     

Skills::~Skills() 
{}

void Skills::BindStrategy(const int* strategy)
{
    for (int i=0; i<SKILLS_NUM; i++)
    {
        this->strategy[i] = strategy[i]; 
    }
}

void Skills::AddExpirience(unsigned long int addExpirience)
{
    expirience += addExpirience;
    while(CheckLevelUp() == true) 
    {}
}

bool Skills::CheckLevelUp()
{
        if (expirience > expirience_nextlevel)
    {
        available_points += 1;
        expirience_nextlevel *= 2;
        level++;
                
                return true;
    }
        
        return false;
}

//######### ATTACK ###############
bool Skills::IncrementAttack()
{
    if (available_points > 0)
    {
        available_points -= 1;
        attack += 1;
        return true;
    }
    
    return false;
}

void Skills::DecrementAttack()
{
    available_points += 1;
    attack -= 1;
}


//######### DEFENCE ###############
bool Skills::IncrementDefence()
{
    if (available_points > 0)
    {
        available_points -= 1;
        defence += 1;
        return true;
    }
    
    return false;  
} 

void Skills::DecrementDefence()
{
    available_points += 1;
    defence -= 1;
}


//######### LEADER ###############
bool Skills::IncrementLeader()
{
    if (available_points > 0)
    {
        available_points -= 1;
        leader += 1;
        return true;
    }
    
    return false;
}

void Skills::DecrementLeader()
{
    available_points += 1;
    leader -= 1;
}


//######### TRADER ###############
bool Skills::IncrementTrader()
{
    if (available_points > 0)
    {
        available_points -= 1;
        trader += 1;
        return true;
    }
    
    return false;
}

void Skills::DecrementTrader()
{
    available_points += 1;
    trader -= 1;
}

//######### TECHNIC ###############
bool Skills::IncrementTechnic()
{
    if (available_points > 0)
    {
        available_points -= 1;
        technic += 1;
        return true;
    }
    
    return false;  
}

void Skills::DecrementTechnic()
{
    available_points += 1;
    technic -= 1;
}


//######### DIMPLOMAT ###############
bool Skills::IncrementDiplomat()
{
    if (available_points > 0)
    {
        available_points -= 1;
        diplomat += 1;
        return true;
    }
    
    return false;
}

void Skills::DecrementDiplomat()
{
    available_points += 1;
    diplomat -= 1;
}

void Skills::Save(boost::property_tree::ptree& save_ptree, const std::string& parent_root) const
{       
    const std::string root = parent_root+"skill.";
        save_ptree.put(root+"attack", attack);        
        save_ptree.put(root+"defence", defence); 
        save_ptree.put(root+"leader", leader);
        save_ptree.put(root+"trader", trader); 
        save_ptree.put(root+"technic", technic); 
        save_ptree.put(root+"diplomat", diplomat); 
        save_ptree.put(root+"available_points", available_points); 

        save_ptree.put(root+"expirience", expirience); 
        save_ptree.put(root+"expirience_nextlevel", expirience_nextlevel); 
}    

void Skills::Load(const boost::property_tree::ptree& load_ptree)
{
        attack = load_ptree.get<int>("attack"); 
        defence = load_ptree.get<int>("defence"); 
        leader = load_ptree.get<int>("leader"); 
        trader = load_ptree.get<int>("trader"); 
        technic = load_ptree.get<int>("technic"); 
        diplomat = load_ptree.get<int>("diplomat"); 
        available_points = load_ptree.get<int>("available_points"); 
        
        expirience = load_ptree.get<int>("expirience"); 
        expirience_nextlevel = load_ptree.get<int>("expirience_nextlevel"); 
}

void Skills::Resolve()
{}

void Skills::ManageAccordingToStrategy()
{
    float strategy_norm[SKILLS_NUM] = {1.,1.,1.,1.,1.,1.};
    for (int i=0; i<SKILLS_NUM; i++)
    {
        strategy_norm[i] = (float)GetSkillDependingOnArrayIndex(i) / strategy[i]; 
    }
    
    int index_min = getIndexWithMinVal(strategy_norm, SKILLS_NUM);
    ImcrementSkillDependingOnArrayIndex(index_min);
        
}

void Skills::ImcrementSkillDependingOnArrayIndex(int i)
{
        switch(i)
        {
                case 0: { IncrementAttack();   break; }
                case 1: { IncrementDefence();  break; }
                case 2: { IncrementLeader();   break; }
                case 3: { IncrementTrader();   break; }
                case 4: { IncrementTechnic();  break; }
                case 5: { IncrementDiplomat(); break; }
        }
}   

int Skills::GetSkillDependingOnArrayIndex(int i)
{
        switch(i)
        {
                case 0: { return attack; break; }
                case 1: { return defence; break; }
                case 2: { return leader; break; }
                case 3: { return trader; break; }
                case 4: { return technic; break; }
                case 5: { return diplomat; break; }
        }
        
        return 0;
}   

const int* getArrayDependingOnClassTypeId(type::ENTITY class_type_id)
{
        switch(class_type_id)
        {
                case type::ENTITY::WARRIOR_ID:   { return SKILLS_STRATEGY_WARRIOR; break; }
                case type::ENTITY::PIRAT_ID:     { return SKILLS_STRATEGY_PIRAT; break; }
                case type::ENTITY::TRADER_ID:    { return SKILLS_STRATEGY_TRADER; break; }
                case type::ENTITY::DIPLOMAT_ID:  { return SKILLS_STRATEGY_DIPLOMAT; break; }
        }
        
        return nullptr;
}

const int* getArrayDependingOnRaceId(type::race race_id)
{
    switch(race_id)
    {
        case type::race::R0_ID: { return SKILLS_STRATEGY_RACE0; break; }
        case type::race::R1_ID: { return SKILLS_STRATEGY_RACE1; break; }
        case type::race::R2_ID: { return SKILLS_STRATEGY_RACE2; break; }
        case type::race::R3_ID: { return SKILLS_STRATEGY_RACE3; break; }
        case type::race::R4_ID: { return SKILLS_STRATEGY_RACE4; break; }
        case type::race::R6_ID: { return SKILLS_STRATEGY_RACE6; break; }
        case type::race::R7_ID: { return SKILLS_STRATEGY_RACE7; break; }
    }
    
    return nullptr;
}
