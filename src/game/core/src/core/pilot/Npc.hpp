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

#include <core/Base.hpp>
#include <core/model/Base.hpp>

#include <core/pilot/Skills.hpp>
#include <core/pilot/Observation.hpp>
#include <core/pilot/AgressorData.hpp>

#include <core/ai/StateMachine.hpp>

#include <ceti/Pack.hpp>

#include <set>

namespace descriptor {
class NpcDescr;
} // namespace descriptor

class BaseAiModel;

class Player;
class GoodsPack;

namespace model {

class Npc : public Base {

public:
    Npc(int_t, int_t);
    ~Npc() = default;
    Npc(const std::string& data);
    std::string data() const;

    //    void setRaceId(race::type race_id)            { m_raceId = race_id; }
    //    void setAiModel(BaseAiModel* ai_model)        { m_aiModel = ai_model; }
    //    void setAlive(bool is_alive)            { m_isAlive = is_alive; }
    //    void setScanTarget(Vehicle* target)    { m_scanTarget = target; }
    //    void setPlayer(Player* player) { m_player = player; }
    //    void setVehicle(Vehicle* vehicle)         { m_vehicle = vehicle; }

    void setCredits(int_t credits) { m_credits = credits; }

    int_t credits() const { return m_credits; }
    race::Type race() const { return m_race; }

    void addAgressor(int_t id) { if (_isWritable()) m_agressors.add(id); }
    void removeAgressor(int_t id) { if (_isWritable()) m_agressors.remove(id); }

    Skills& skills() { return m_skills; }
    ceti::pack<int_t> agressors() const { return m_agressors; }

private:
    race::Type m_race = race::Type::NONE;
    int_t m_credits;

    int_t m_player = NONE;
    int_t m_vehicle = NONE;

    Skills m_skills;

    int_t m_aiModel = NONE;

    int_t m_scanTarget = NONE;

    ceti::pack<int_t> m_agressors;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_race;
        ar & m_credits;
        ar & m_player;
        ar & m_vehicle;
        //ar & m_skills;
        ar & m_aiModel;
        ar & m_scanTarget;
        ar & m_agressors;
    }
};

} // namespace model

namespace core {
namespace control {

class Vehicle;
class SpaceObject;
class StarSystem;
class Planet;

class Npc : public Base
{
public:
    Npc(descriptor::NpcDescr*, model::Npc*);
    virtual ~Npc();

    // model interface
    race::Type race() const;
    //

    virtual void putChildrenToGarbage() const {}

    void setVehicle(Vehicle* vehicle) { m_vehicle = vehicle; }

    Player* player() const { return m_player; }
    Vehicle* vehicle() const { return m_vehicle; }
    Observation& observation() { return m_observation; }

    StateMachine& stateMachine() { return m_stateMachine; }

    StarSystem* starsystem() const;

    void increaseCredits(int credits) { model()->setCredits(model()->credits() + credits); }
    bool withdrawCredits(int_t);
    void addExpirience(int, bool);

    void cloneMacroTaskFrom(model::Npc*);

    // AI
    void remeberAgressor(SpaceObject*);
    void update(int);

    void updateInSpaceInStatic();
    void updateInKosmoportInStatic();
    //

    //// scanning
    bool isAbleToScan(Vehicle*);
    bool tryScan(Vehicle*, bool check = true);
//    bool scanProceeding();
    void resetScanTarget();
    //// scanning

    Planet* planetForDocking();
    StarSystem* closestStarSystem(int);

    void renderInfo(const glm::vec2&);

    //bool BuyArmorAsMuchAsPossible();
    bool buyGoods();

    void applySkillsStrategy();

    std::string agressorSetString() const;

    model::Npc* model() const { return m_model_npc; }

    bool isAgressor(int_t) const;

    Vehicle* scanTarget() const { return m_scanTarget; }

protected:
    void _setScanTarget(Vehicle* scanTarget);

private:
    descriptor::NpcDescr* m_descriptor_npc = nullptr;
    model::Npc* m_model_npc = nullptr;

    //bool m_isAlive = true;
    int_t m_race = NONE;

    Player* m_player = nullptr;
    Vehicle* m_vehicle = nullptr;
    Vehicle* m_scanTarget = nullptr;

    BaseAiModel* m_aiModel = nullptr;
    StateMachine m_stateMachine;

//    std::set<AgressorData, AgressorDataComparator> m_agressorsData;

    Observation m_observation;

    void __scenarioFireVehicleAgressor();
    void __scenarioFireAsteroid();

    void __updateInfo();
};


} // namespace controller
} // namespace core


//class Npc : public model::Base
//{
//public:
//    Npc(int, entity::Type, entity::Type);
//    virtual ~Npc();

//    virtual void putChildrenToGarbage() const {}

//    void setRaceId(race::type race_id)            { m_raceId = race_id; }
//    void setAiModel(BaseAiModel* ai_model)        { m_aiModel = ai_model; }
//    void setAlive(bool is_alive)            { m_isAlive = is_alive; }
//    void setScanTarget(Vehicle* target)    { m_scanTarget = target; }
//    void setPlayer(Player* player) { m_player = player; }
//    void setVehicle(Vehicle* vehicle)         { m_vehicle = vehicle; }

//    race::type raceId() const { return m_raceId; }

//    Player* player() const { return m_player; }
//    Vehicle* vehicle() const { return m_vehicle; }
//    Skills& skills() { return m_skills; }
//    Vehicle* scanTarget() const { return m_scanTarget; }
//    Observation& observation() { return m_observation; }
//    unsigned long int credits() const { return m_credits; }
//    StateMachine& stateMachine() { return m_stateMachine; }

//    Starsystem* starsystem() const;

//    void increaseCredits(unsigned long int credits) { m_credits += credits; }
//    bool withdrawCredits(unsigned long int);
//    void addExpirience(int, bool);

//    void cloneMacroTaskFrom(Npc*);

//    // AI
//    void remeberAgressor(Vehicle*);
//    void updateInSpace(int, bool);

//    void updateInSpaceInStatic();
//    void updateInKosmoportInStatic();
//    //

//    //// scanning
//    bool isAbleToScan(Vehicle*);
//    bool scanProceeding();
//    void resetScanTarget();
//    //// scanning

//    Planet* planetForDocking();
//    Starsystem* closestStarSystem(int);

//    void renderInfo(const glm::vec2&);

//    //bool BuyArmorAsMuchAsPossible();
//    bool buyGoods();

//    void Save(boost::property_tree::ptree&) const;
//    void Load(const boost::property_tree::ptree&);
//    void Resolve();

//    void applySkillsStrategy();

//    std::string agressorSetString() const;

//private:
//    bool m_isAlive;
//    race::type m_raceId;
//    unsigned long int m_credits;

//    Player* m_player;
//    Vehicle* m_vehicle;

//    Skills m_skills;

//    BaseAiModel* m_aiModel;
//    StateMachine m_stateMachine;

//    //        InfoTable info;

//    std::set<AgressorData, AgressorDataComparator> m_agressorsData;

//    Vehicle* m_scanTarget;

//    Observation m_observation;

//    //UnresolvedDataNpc data_unresolved_npc;

//    void __scenarioFireVehicleAgressor();
//    void __scenarioFireAsteroid();

//    void __updateInfo();

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
//};




