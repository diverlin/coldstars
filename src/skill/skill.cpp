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


#include "skill.hpp"

Skill :: Skill()
{
	attack   = getRandInt(0, 5);
	defence  = getRandInt(0, 5);
	leader   = getRandInt(0, 5);
	trader   = getRandInt(0, 5);
	technic  = getRandInt(0, 5);
	diplomat = getRandInt(0, 5);  

	acknowledge();

	available_points = 3;

	expirience = getRandInt(40, 400);
	expirience_for_next_level = 1000;
}     

Skill :: ~Skill()
{}



int Skill :: getAttack()   const { return attack; }
int Skill :: getDefence()  const { return defence; }  
int Skill :: getLeader()   const { return leader; }  
int Skill :: getTrader()   const { return trader; }   
int Skill :: getTechnic()  const { return technic; }  
int Skill :: getDiplomat() const { return diplomat; }



void Skill :: addExpirience(unsigned long int addExpirience)
{
	expirience += addExpirience;
	if (expirience > expirience_for_next_level)
	{
		available_points += 1;
		expirience_for_next_level *= 2;
	}
}


void Skill :: acknowledge()
{
	attack_undo   = 0;
	defence_undo  = 0;
	leader_undo   = 0;
	trader_undo   = 0;
	technic_undo  = 0;
	diplomat_undo = 0;
}

//######### ATTACK ###############
void Skill :: incrementAttack()
{
	if (available_points > 0)
	{
		available_points -= 1;
		attack += 1;
		attack_undo += 1;
	}
}

void Skill :: decrementAttack()
{
	if (attack_undo > 0)
	{ 
		available_points += 1;
		attack -= 1;
		attack_undo -= 1;
	}
}


//######### DEFENCE ###############
void Skill :: incrementDefence()
{
	if (available_points > 0)
	{
		available_points -= 1;
		defence += 1;
		defence_undo += 1;
	}  
} 

void Skill :: decrementDefence()
{
	if (defence_undo > 0)
	{
		available_points += 1;
		defence -= 1;
		defence_undo -= 1;
	}
}


//######### LEADER ###############
void Skill :: incrementLeader()
{
	if (available_points > 0)
	{
		available_points -= 1;
		leader += 1;
		leader_undo += 1;
	}
}

void Skill :: decrementLeader()
{
	if (leader_undo > 0)
	{
		available_points += 1;
		leader -= 1;
		leader_undo -= 1;
	}
}


//######### TRADER ###############
void Skill :: incrementTrader()
{
	if (available_points > 0)
	{
		available_points -= 1;
		trader += 1;
		trader_undo += 1; 
	}
}

void Skill :: decrementTrader()
{
	if (trader_undo > 0)
	{
		available_points += 1;
		trader -= 1;
		trader_undo -= 1;
	}
}

//######### TECHNIC ###############
void Skill :: incrementTechnic()
{
	if (available_points > 0)
	{
		available_points -= 1;
		technic += 1;
		technic_undo += 1;
	}  
}

void Skill :: decrementTechnic()
{
	if (technic_undo > 0)
	{
		available_points += 1;
		technic -= 1;
		technic_undo -= 1;
	}
}


//######### DIMPLOMAT ###############
void Skill :: incrementDiplomat()
{
	if (available_points > 0)
	{
		available_points -= 1;
		diplomat += 1;
		diplomat_undo += 1; 
	}
}

void Skill :: decrementDiplomat()
{
	if (diplomat_undo > 0)
	{
		available_points += 1;
		diplomat -= 1;
		diplomat_undo -= 1;
	}
}



