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

#ifndef NPC_HPP
#define NPC_HPP

#include <set>

#include "../common/Base.hpp"
class BaseAiModel;
#include "../pilots/Skills.hpp"
#include "../ai/StateMachine.hpp"
class Vehicle;
class Player;
#include "Observation.hpp" 
class Planet;
class GoodsPack;
class StarSystem;
#include "../text/InfoTable.hpp"
#include "../pilots/AgressorData.hpp"

struct UnresolvedDataNpc
{
    int vehicle_id;    
    int aiModel_id;
    
    Task macrotask;
    Task microtask;
};

class Npc : public Base
{
       public:
        Npc(int, TYPE::ENTITY, TYPE::ENTITY);                      
        virtual ~Npc();
        
        virtual void PutChildsToGarbage() const {};
        
        void SetRaceId(TYPE::RACE race_id)            { this->race_id = race_id; };
        void SetAiModel(BaseAiModel* ai_model)        { this->ai_model = ai_model; };
        void SetAlive(bool is_alive)            { this->is_alive = is_alive; }
        void SetScanTarget(Vehicle* vehicle_to_scan)    { this->vehicle_to_scan = vehicle_to_scan; };
        void SetPlayer(Player* player) { this->player = player; };
        void SetVehicle(Vehicle* vehicle)         { this->vehicle = vehicle; };

        TYPE::RACE GetRaceId()            const { return race_id; };

        Player* GetPlayer() const { return player; };
        Vehicle* GetVehicle()           const { return vehicle; };
        Skills& GetSkills()         { return skills; };
        Vehicle* GetScanTarget()        const { return vehicle_to_scan; };
        Observation& GetObservation()   { return observation; };
        INTLONGEST GetCredits()  const { return credits; };   
        StateMachine& GetStateMachine() { return state_machine; };

        StarSystem* GetStarSystem() const;

        void IncreaseCredits(INTLONGEST credits) { this->credits += credits; };
        bool WithdrawCredits(INTLONGEST);
     
        void AddExpirience(int, bool);
        
        void CloneMacroTaskFrom(Npc*);
        
        // AI
        void TakeIntoAccountAgressor(Vehicle*);
        void UpdateInSpace(int, bool);
        
        void UpdateInSpaceInStatic();
        void UpdateInKosmoportInStatic();
        //
        
        //// scanning
        bool CheckPossibilityToScan(Vehicle*);
        bool ScanProceeding(); 
        void ResetScanTarget();
        //// scanning
        
        Planet* GetPlanetForDocking();
        StarSystem* GetClosestStarSystem(int);
        
        void RenderInfo(const glm::vec2&);
        
        //bool BuyArmorAsMuchAsPossible();
        bool BuyGoods();
        
        void Save(boost::property_tree::ptree&) const;
        void Load(const boost::property_tree::ptree&);
        void Resolve();
        
        void ApplySkillsStrategy();
        
        std::string GetAgressorSetString() const;              

       private:
        bool is_alive;
        TYPE::RACE race_id;
        INTLONGEST credits; 
        
        Player* player;
        Vehicle* vehicle;
        
        Skills skills;
        
        BaseAiModel* ai_model;
        StateMachine state_machine;
        
        InfoTable info;
        
        std::set<AgressorData, AgressorDataComparator> data_agressor_set;
        
        Vehicle* vehicle_to_scan;
        
        Observation observation;
        
        UnresolvedDataNpc data_unresolved_npc;
        
        void ScenarioFireVehicleAgressor();
        void ScenarioFireAsteroid();
        
        void UpdateInfo();
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;        
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};


#endif 

