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


#include <ai/God.hpp>

#include <ceti/Logger.hpp>
#include <meti/RandUtils.hpp>
#include <common/constants.hpp>
#include <common/GameDate.hpp>
#include <common/Global.hpp>

#include <world/galaxy.hpp>
#include <world/Sector.hpp>
#include <world/starsystem.hpp>

#include <builder/dock/KosmoportBuilder.hpp>
#include <builder/dock/NatureLandBuilder.hpp>
#include <builder/pilots/NpcBuilder.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/spaceobjects/SpaceStationBuilder.hpp>
#include <builder/spaceobjects/SatelliteBuilder.hpp>
#include <builder/world/GalaxyBuilder.hpp>

#include <spaceobjects/ALL>

#include <dock/Kosmoport.hpp>
#include <dock/NatureLand.hpp>

#include <ai/Task.hpp>
#include <pilots/Npc.hpp>

#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/RaceDescriptors.hpp>
#include <descriptors/VehicleDescriptorGenerator.hpp>

#include <meti/RandUtils.hpp>
#include <math/rand.hpp>


God::God()
:
m_DateLastUpdate(0,0,0)
{}
        
God::~God()
{}

Galaxy* God::createWorld(const GalaxyDescriptor& galaxy_descriptor)
{
    Galaxy* galaxy = global::get().galaxyBuilder().create(galaxy_descriptor);
    CreateLife(galaxy, galaxy_descriptor);
    if (galaxy_descriptor.allow_invasion == true) {
        CreateInvasion(galaxy, galaxy_descriptor);
    }

    bool player2space = true;
    StarSystem* const starsystem = galaxy->GetRandomSector()->randomStarSystem();
    if (player2space == true) {
        glm::vec3 center(500, 500, DEFAULT_ENTITY_ZPOS);
        glm::vec3 angle(0,0,0);
        //starsystem->AddVehicle(player->GetNpc()->GetVehicle(), center, angle, nullptr);
    } else {
        //starsystem->GetRandomPlanet()->GetLand()->AddVehicle(player->GetNpc()->GetVehicle());
    }

    CreateShips(starsystem, /*ships_num=*/20, TYPE::RACE::R0_ID);   // fake

    return galaxy;
}

void God::CreateLife(Galaxy* galaxy, const GalaxyDescriptor& galaxy_descriptor) const
{
//    for(unsigned int i=0; i<galaxy->m_sectors.size(); i++) {
//        for(unsigned int j=0; j<galaxy->m_sectors[i]->m_starsystems.size(); j++) {
//            const StarSystemDescriptor& starsystem_descriptor = galaxy_descriptor.sector_descriptors[i].starsystem_descriptors[j];
//            StarSystem* starsystem = galaxy->m_sectors[i]->m_starsystems[j];
//            for(unsigned int j=0; j<starsystem->m_planets.size(); j++) {
//                CreateLifeAtPlanet(starsystem->m_planets[j], starsystem_descriptor);
//            }
//            CreateSpaceStations(starsystem, starsystem_descriptor.spacestation_num);
//        }
//    }
}

void God::CreateInvasion(Galaxy* galaxy, const GalaxyDescriptor& galaxy_descriptor) const
{
    for (unsigned int i=0; i<INITIATE_STARSYSTEM_IVASION_NUM; i++) {
        StarSystem* starsystem = galaxy->GetRandomSector()->randomStarSystem(ENTITY::STARSYSTEM::CONDITION::SAFE_ID);
        TYPE::RACE race_id = (TYPE::RACE)meti::getRandInt((int)TYPE::RACE::R6_ID, (int)TYPE::RACE::R7_ID);
        int ship_num = meti::getRandInt(ENTITY::STARSYSTEM::SHIPENEMY_INIT_MIN, ENTITY::STARSYSTEM::SHIPENEMY_INIT_MAX);
        CreateShips(starsystem, ship_num, race_id);
    }
}

void God::ProceedInvasion(Galaxy* galaxy) const
{
    StarSystem* starsystem_invade_from = galaxy->GetRandomSector()->randomStarSystem(ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID);
    if (starsystem_invade_from == nullptr) {
        return;
    }
    
    StarSystem* starsystem_invade_to   = galaxy->GetClosestSectorTo(starsystem_invade_from->sector())->closestStarSystemTo(starsystem_invade_from, ENTITY::STARSYSTEM::CONDITION::SAFE_ID);
    if (starsystem_invade_to == nullptr) {
        return;
    }
    
    Npc* npc_leader = starsystem_invade_from->freeLeaderByRaceId(starsystem_invade_from->conquerorRaceId());
    Task macrotask(TYPE::AISCENARIO::MACRO_STARSYSTEMLIBERATION_ID, starsystem_invade_to->id());
    npc_leader->GetStateMachine().SetCurrentMacroTask(macrotask);
    
    int num_max= 10;
    starsystem_invade_from->createGroupAndShareTask(npc_leader, starsystem_invade_to, num_max);
}

void God::update(Galaxy* galaxy, const GameDate& date)
{
    if (m_DateLastUpdate - date >= GOD_REST_IN_DAYS)
    {
        LOG("God::Update");
            
        galaxy->FillStarSystemsCondition(data_starsystems_condition);
        m_DateLastUpdate = date;
        
        ProceedInvasion(galaxy);

        LOG(data_starsystems_condition.GetStr());
    }
}                
     
void God::CreateLifeAtPlanet(Planet* planet, const StarSystemDescriptor& starsystem_descriptor) const
{            
//    unsigned long int population = 0;
//    meti::getRandBool() ? population = meti::getRandInt(POPULATION_MIN, POPULATION_MAX) : population = 0;
//    planet->SetPopulation(population);
    
//    Land* land = nullptr;
//    if (population > 0) { land = global::get().kosmoportBuilder().create(); }
//    else                { land = global::get().natureLandBuilder().create(); }
        
//    planet->BindLand(land);

//    if (population > 0)
//    {
//        if (starsystem_descriptor.allow_satellites == true)
//        {
//            int sattelitewarriors_num = 1; //getRandInt(SATELLITEWARRIORS_PER_PLANET_MIN, SATELLITEWARRIORS_PER_PLANET_MAX);
//            for (int j=0; j<sattelitewarriors_num; j++)
//            {
//                Satellite* satellite = global::get().satelliteBuilder().create();
//                global::get().satelliteBuilder().equip(satellite); // improove
            
//                {
//                    TYPE::RACE npc_race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
//                    TYPE::ENTITY npc_subtype_id    = TYPE::ENTITY::WARRIOR_ID;
//                    TYPE::ENTITY npc_subsubtype_id = TYPE::ENTITY::WARRIOR_ID;
            
//                    Npc* npc = global::get().npcBuilder().create(npc_race_id, npc_subtype_id, npc_subsubtype_id);
//                    satellite->BindOwnerNpc(npc);
//                }
            
//                glm::vec3 orbit_center(0, 0, DEFAULT_ENTITY_ZPOS);
//                glm::vec3 angle(0,0,0);
//                planet->starsystem()->add(satellite, orbit_center, angle, planet);
//            }
//        }
        
//        if (starsystem_descriptor.allow_ships == true)
//        {
//            std::vector<TYPE::ENTITY> allowed_subtypes;
//            if (starsystem_descriptor.allow_ship_ranger == true)      { allowed_subtypes.push_back(TYPE::ENTITY::RANGER_ID); }
//            if (starsystem_descriptor.allow_ship_warrior == true)     { allowed_subtypes.push_back(TYPE::ENTITY::WARRIOR_ID); }
//            if (starsystem_descriptor.allow_ship_trader == true)      { allowed_subtypes.push_back(TYPE::ENTITY::TRADER_ID); }
//            if (starsystem_descriptor.allow_ship_pirat == true)       { allowed_subtypes.push_back(TYPE::ENTITY::PIRAT_ID); }
//            if (starsystem_descriptor.allow_ship_diplomat == true)    { allowed_subtypes.push_back(TYPE::ENTITY::DIPLOMAT_ID); }
            
//            int ship_num = meti::getRandInt(SHIPINIT_PER_PLANET_MIN, SHIPINIT_PER_PLANET_MAX);
//            for (int j=0; j<ship_num; j++)
//            {
//                TYPE::RACE npc_race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
//                TYPE::ENTITY npc_subtype_id    = getRandNpcSubTypeId(npc_race_id, allowed_subtypes);
//                TYPE::ENTITY npc_subsubtype_id = getRandNpcSubSubTypeId(npc_subtype_id);
                       
//                Ship* new_ship = global::get().shipBuilder().create(generateVehicleDescriptor());
//                global::get().shipBuilder().equip(new_ship); // improove
//                //ShipBuilder::Instance().EquipModules(ship, tech_level);
//                //ShipBuilder::Instance().EquipArtefacts(ship, tech_level);
//                //ShipBuilder::Instance().EquipBomb(ship, tech_level);
            
//                Npc* new_npc = global::get().npcBuilder().create(npc_race_id, npc_subtype_id, npc_subsubtype_id);
//                new_ship->BindOwnerNpc(new_npc);
                
//                planet->AddVehicle(new_ship);
//            }
//        }
//    }
}

void God::CreateSpaceStations(StarSystem* starsystem, int spacestation_per_system) const
{       
    for (int i=0; i<spacestation_per_system; i++)
    {     
        TYPE::RACE npc_race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
        TYPE::ENTITY npc_subtype_id    = TYPE::ENTITY::WARRIOR_ID;
        TYPE::ENTITY npc_subsubtype_id = TYPE::ENTITY::WARRIOR_ID;
            
        //TYPE::RACE ship_race_id = npc_race_id;         // RACES_ALL_vec[getRandInt(0, RACES_ALL_vec.size())];
        //TYPE::ENTITY ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_vec[getRandInt(0, SHIP_SUBTYPE_vec.size())];
        //int weapons_num = 5;
        
        SpaceStation* spacestation = global::get().spaceStationBuilder().create();
        global::get().spaceStationBuilder().equip(spacestation);  // improove

        Npc* npc = global::get().npcBuilder().create(npc_race_id, npc_subtype_id, npc_subsubtype_id);
        spacestation->BindOwnerNpc(npc);

        glm::vec2 center = meti::getRandVec2f(700, 1500);
        glm::vec3 center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
        glm::vec3 angle(0,0,meti::getRandInt(0, 360));
                        
        starsystem->add(spacestation, center3, angle, nullptr);
        
        {  
            Satellite* satellite = global::get().satelliteBuilder().create();
            global::get().satelliteBuilder().equip(satellite);                   // improove

            Npc* new_npc = global::get().npcBuilder().create(npc_race_id, npc_subtype_id, npc_subsubtype_id);
            satellite->BindOwnerNpc(new_npc);
            
            glm::vec3 center(0, 0, DEFAULT_ENTITY_ZPOS);
            glm::vec3 angle(0, 0, 0);
                            
            starsystem->add(satellite, center, angle, spacestation);
        }
    }        
}

void God::CreateShips(StarSystem* starsystem, int ship_num, TYPE::RACE npc_race_id, TYPE::ENTITY subtype_id, TYPE::ENTITY subsubtype_id) const
{
    TYPE::ENTITY npc_subtype_id = TYPE::ENTITY::NONE_ID;
    TYPE::ENTITY npc_subsubtype_id = TYPE::ENTITY::NONE_ID;

    for (int i=0; i<ship_num; i++)
    {
        // VERY UGLY LOGIC START (TODO)
        if (subtype_id == TYPE::ENTITY::NONE_ID) {
            npc_subtype_id    = getRandNpcSubTypeId(npc_race_id);
        } else {
            npc_subtype_id    = subtype_id;
        }   

        if (subsubtype_id == TYPE::ENTITY::NONE_ID) {
            npc_subsubtype_id = getRandNpcSubSubTypeId(npc_subtype_id);
        } else {
            npc_subsubtype_id = subsubtype_id;
        }
        // VERY UGLY LOGIC END

        Ship* new_ship = global::get().shipBuilder().create();
        global::get().shipBuilder().equip(new_ship); // improove

        Npc* new_npc = global::get().npcBuilder().create(npc_race_id, npc_subtype_id, npc_subsubtype_id);
        new_ship->BindOwnerNpc(new_npc);

        glm::vec3 center = meti::getRandXYVec3f(300, 1200, DEFAULT_ENTITY_ZPOS);
        glm::vec3 angle(0, 0, meti::getRandInt(0, 360));
        starsystem->add(new_ship, center, angle, nullptr);
    }
}
