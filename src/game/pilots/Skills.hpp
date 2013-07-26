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


#ifndef SKILLS_H
#define SKILLS_H

#include <boost/property_tree/ptree.hpp>
#include "../common/constants.hpp"
#include "../common/RaceTypes.hpp"

class Skills
{ 
	public:
		Skills();
		~Skills();

                void BindStrategy(const int*);
                
		int GetAvailablePoints() const	{ return available_points; };
		int GetExpirience()  const { return expirience; };
		int GetExpirienceNextLevel() const { return expirience_nextlevel; };
		int GetLevel() const { return level; };

		float GetAttackNormalized()   const { return attack  * SKILLS::ATTACK_NORMALIZED_RATE; };   
		float GetDefenceNormalized()  const { return defence * SKILLS::DEFENCE_NORMALIZED_RATE; }; 
		
		int GetAttack()   const { return attack; };   
		int GetDefence()  const { return defence; };  
		int GetLeader()   const { return leader; };  
		int GetTrader()   const { return trader; };   
		int GetTechnic()  const { return technic; };  
		int GetDiplomat() const { return diplomat; }; 

		void AddExpirience(unsigned long int expirience);

		bool IncrementAttack();
		void DecrementAttack();

		bool IncrementDefence();
		void DecrementDefence();

		bool IncrementLeader();
		void DecrementLeader();

		bool IncrementTrader();
		void DecrementTrader();

		bool IncrementTechnic();
		void DecrementTechnic();

		bool IncrementDiplomat();
		void DecrementDiplomat();
                
                void ManageAccordingToStrategy();

		void SaveData(boost::property_tree::ptree&, const std::string&) const;
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
		
	private:
		int attack;   
		int defence;  
		int leader;  
		int trader;   
		int technic;  
		int diplomat; 

		int available_points;
		int level;
		
		unsigned long int expirience;
		unsigned long int expirience_nextlevel;
                
        int strategy[SKILLS_NUM];
                
        void ImcrementSkillDependingOnArrayIndex(int);
        int GetSkillDependingOnArrayIndex(int); 
        
        bool CheckLevelUp();               
};

const int* getArrayDependingOnClassTypeId(int);
const int* getArrayDependingOnRaceId(TYPE::RACE);

#endif


