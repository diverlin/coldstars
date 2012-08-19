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

#ifndef NPC_H
#define NPC_H

#include "../ai/aiModel/BaseAiModel.hpp"
#include "../pilots/Skill.hpp"
#include "../pilots/Observation.hpp" 
#include "../ai/StateMachine.hpp"

class Planet;
class GoodsPack;

struct UnresolvedDataUniqueNpc
{
	int vehicle_id;	
	int aiModel_id;
};

class Npc : public Base
{
   	public:
              	Npc(int);              	    
     		virtual ~Npc();    		
     		
     		void SetRaceId(int race_id)			{ this->race_id = race_id; };
     		void SetAiModel(BaseAiModel* ai_model)		{ this->ai_model = ai_model; };
		void SetAlive(bool is_alive)			{ this->is_alive = is_alive; }
		void SetScanTarget(Vehicle* vehicle_to_scan)	{ this->vehicle_to_scan = vehicle_to_scan; };
		void SetUpperControl(bool upper_control)       { this->upper_control = upper_control; };
		void SetVehicle(Vehicle* vehicle) 		{ this->vehicle = vehicle; };

		int GetRaceId()				const { return race_id; };
		StarSystem* GetFailBackStarSystem() 	const { return failback_starsystem; };
		Vehicle* GetVehicle()           	const { return vehicle; };
		Skill& GetSkill() 			{ return skill; };
		Vehicle* GetScanTarget()        	const { return vehicle_to_scan; };	
		Observation& GetObservation()   	{ return observation; };
		unsigned long int GetCredits()  	const { return credits; };   
		StateMachine* GetStateMachine() 	const { return state_machine; };

		StarSystem* GetStarSystem() const;

		void IncreaseCredits(int credits) { this->credits += credits; };
		void DecreaseCredits(int credits) { this->credits -= credits; };
     
     		// AI
     		void UpdateInSpace(int, bool);

     		void MindInSpace();         		     		
     		void MindInKosmoport();
                //

     		//// scanning
    		bool CheckPossibilityToScan(Vehicle*);
     		bool ScanProceeding(); 
     		void ResetScanTarget();
     		//// scanning
     		
     		Planet* GetPlanetForDocking();
    		StarSystem* GetClosestStarSystem(bool);
    		
                NeedsToDo needsToDo;

		void RenderInfo(const vec2f&);
		                   
                //bool BuyArmorAsMuchAsPossible();
                bool BuyGoods();
                bool SellGoods(GoodsPack*);
                                
                void SaveData(boost::property_tree::ptree&) const;		
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
		
   	private:
   		bool is_alive;
     		int race_id;
     		unsigned long int credits; 
     		bool upper_control;

   	     	StarSystem* failback_starsystem;
   	     	     		     		
   	     	Vehicle* vehicle;
   	     	
   	     	Skill skill; 


     		BaseAiModel* ai_model;
     		StateMachine* state_machine;
   		     	
   		InfoTable info;
     		 	
     		Vehicle* vehicle_to_scan;
     		
                Observation observation;

		UnresolvedDataUniqueNpc data_unresolved_npc;

                void AsteroidScenario();
                void CheckNeeds();
                                    		
		void UpdateInfo();	     	
    		
     		void SaveDataUniqueNpc(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueNpc(const boost::property_tree::ptree&);
		void ResolveDataUniqueNpc();
 };


#endif 

