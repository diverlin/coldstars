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

#include <set>

#include <common/Base.hpp>

#include <pilots/Skills.hpp>
#include <ai/StateMachine.hpp>
#include <pilots/Observation.hpp>
#include <pilots/AgressorData.hpp>

class BaseAiModel;
class Vehicle;
class Player;
class Planet;
class GoodsPack;
class Starsystem;

struct UnresolvedDataNpc
{
    int vehicle_id;
    int aiModel_id;

    Task macrotask;
    Task microtask;
};

class Npc : public core::Base
{
public:
    Npc(int, type::entity, type::entity);
    virtual ~Npc();

    virtual void putChildrenToGarbage() const {}

    void setRaceId(type::race race_id)            { m_raceId = race_id; }
    void setAiModel(BaseAiModel* ai_model)        { m_aiModel = ai_model; }
    void setAlive(bool is_alive)            { m_isAlive = is_alive; }
    void setScanTarget(Vehicle* target)    { m_scanTarget = target; }
    void setPlayer(Player* player) { m_player = player; }
    void setVehicle(Vehicle* vehicle)         { m_vehicle = vehicle; }

    type::race raceId() const { return m_raceId; }

    Player* player() const { return m_player; }
    Vehicle* vehicle() const { return m_vehicle; }
    Skills& skills() { return m_skills; }
    Vehicle* scanTarget() const { return m_scanTarget; }
    Observation& observation() { return m_observation; }
    unsigned long int credits() const { return m_credits; }
    StateMachine& stateMachine() { return m_stateMachine; }

    Starsystem* starsystem() const;

    void increaseCredits(unsigned long int credits) { m_credits += credits; }
    bool withdrawCredits(unsigned long int);
    void addExpirience(int, bool);

    void cloneMacroTaskFrom(Npc*);

    // AI
    void remeberAgressor(Vehicle*);
    void updateInSpace(int, bool);

    void updateInSpaceInStatic();
    void updateInKosmoportInStatic();
    //

    //// scanning
    bool isAbleToScan(Vehicle*);
    bool scanProceeding();
    void resetScanTarget();
    //// scanning

    Planet* planetForDocking();
    Starsystem* closestStarSystem(int);

    void renderInfo(const glm::vec2&);

    //bool BuyArmorAsMuchAsPossible();
    bool buyGoods();

    void Save(boost::property_tree::ptree&) const;
    void Load(const boost::property_tree::ptree&);
    void Resolve();

    void applySkillsStrategy();

    std::string agressorSetString() const;

private:
    bool m_isAlive;
    type::race m_raceId;
    unsigned long int m_credits;

    Player* m_player;
    Vehicle* m_vehicle;

    Skills m_skills;

    BaseAiModel* m_aiModel;
    StateMachine m_stateMachine;

    //        InfoTable info;

    std::set<AgressorData, AgressorDataComparator> m_agressorsData;

    Vehicle* m_scanTarget;

    Observation m_observation;

    UnresolvedDataNpc data_unresolved_npc;

    void __scenarioFireVehicleAgressor();
    void __scenarioFireAsteroid();

    void __updateInfo();

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();
};




