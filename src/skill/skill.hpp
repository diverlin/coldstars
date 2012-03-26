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


#ifndef SKILL_H
#define SKILL_H


class Skill
{ 
	public:
		Skill();
		~Skill();

		int getAttack()   const;   
		int getDefence()  const;  
		int getLeader()   const;  
		int getTrader()   const;   
		int getTechnic()  const;  
		int getDiplomat() const; 

		void addExpirience(unsigned long int expirience);
		void acknowledge();

		void incrementAttack();
		void decrementAttack();

		void incrementDefence();
		void decrementDefence();

		void incrementLeader();
		void decrementLeader();

		void incrementTrader();
		void decrementTrader();

		void incrementTechnic();
		void decrementTechnic();

		void incrementDiplomat();
		void decrementDiplomat();

	private:
		int attack;   
		int defence;  
		int leader;  
		int trader;   
		int technic;  
		int diplomat; 

		int attack_undo;
		int defence_undo;
		int leader_undo;
		int trader_undo;
		int technic_undo;
		int diplomat_undo;

		int available_points;

		unsigned long int expirience;
		unsigned long int expirience_for_next_level;

};

#endif


