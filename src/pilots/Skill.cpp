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


#include "Skill.hpp"
#include "../common/constants.hpp"

Skill::Skill():
attack(SKILL::ATTACK_MIN),
defence(SKILL::DEFENCE_MIN),
leader(SKILL::LEADER_MIN),
trader(SKILL::TRADER_MIN),
technic(SKILL::TECHNIC_MIN),
diplomat(SKILL::DIPLOMAT_MIN),
attack_undo(0),
defence_undo(0),
leader_undo(0),
trader_undo(0),
technic_undo(0),
diplomat_undo(0),	
available_points(6),
expirience(0),
expirience_nextlevel(SKILL::EXPIRIENCE_THRESHOLD),
level(1)
{}     

Skill::~Skill()
{}

void Skill::AddExpirience(unsigned long int addExpirience)
{
	expirience += addExpirience;
	if (expirience > expirience_nextlevel)
	{
		available_points += 1;
		expirience_nextlevel *= 2;
		level++;
	}
}

void Skill::Acknowledge()
{
	attack_undo   = 0;
	defence_undo  = 0;
	leader_undo   = 0;
	trader_undo   = 0;
	technic_undo  = 0;
	diplomat_undo = 0;
}

//######### ATTACK ###############
void Skill::IncrementAttack()
{
	if (available_points > 0)
	{
		available_points -= 1;
		attack += 1;
		attack_undo += 1;
	}
}

void Skill::DecrementAttack()
{
	if (attack_undo > 0)
	{ 
		available_points += 1;
		attack -= 1;
		attack_undo -= 1;
	}
}


//######### DEFENCE ###############
void Skill::IncrementDefence()
{
	if (available_points > 0)
	{
		available_points -= 1;
		defence += 1;
		defence_undo += 1;
	}  
} 

void Skill::DecrementDefence()
{
	if (defence_undo > 0)
	{
		available_points += 1;
		defence -= 1;
		defence_undo -= 1;
	}
}


//######### LEADER ###############
void Skill::IncrementLeader()
{
	if (available_points > 0)
	{
		available_points -= 1;
		leader += 1;
		leader_undo += 1;
	}
}

void Skill::DecrementLeader()
{
	if (leader_undo > 0)
	{
		available_points += 1;
		leader -= 1;
		leader_undo -= 1;
	}
}


//######### TRADER ###############
void Skill::IncrementTrader()
{
	if (available_points > 0)
	{
		available_points -= 1;
		trader += 1;
		trader_undo += 1; 
	}
}

void Skill::DecrementTrader()
{
	if (trader_undo > 0)
	{
		available_points += 1;
		trader -= 1;
		trader_undo -= 1;
	}
}

//######### TECHNIC ###############
void Skill::IncrementTechnic()
{
	if (available_points > 0)
	{
		available_points -= 1;
		technic += 1;
		technic_undo += 1;
	}  
}

void Skill::DecrementTechnic()
{
	if (technic_undo > 0)
	{
		available_points += 1;
		technic -= 1;
		technic_undo -= 1;
	}
}


//######### DIMPLOMAT ###############
void Skill::IncrementDiplomat()
{
	if (available_points > 0)
	{
		available_points -= 1;
		diplomat += 1;
		diplomat_undo += 1; 
	}
}

void Skill::DecrementDiplomat()
{
	if (diplomat_undo > 0)
	{
		available_points += 1;
		diplomat -= 1;
		diplomat_undo -= 1;
	}
}

void Skill::SaveData(boost::property_tree::ptree& save_ptree, const std::string& parent_root) const
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

void Skill::LoadData(const boost::property_tree::ptree& load_ptree)
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

void Skill::ResolveData()
{}
