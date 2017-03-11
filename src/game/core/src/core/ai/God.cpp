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

#include <common/constants.hpp>
#include <common/Global.hpp>
#include <common/TurnTimer.hpp>
#include <common/GameDate.hpp>

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

#include <core/descriptor/GalaxyDescriptor.hpp>
#include <core/descriptor/RaceDescriptors.hpp>

#include <math/rand.hpp>

#include <managers/EntityManager.hpp> // garbage

#include <meti/RandUtils.hpp>
#include <meti/RandUtils.hpp>

#include <ceti/Logger.hpp>


God::God()
    :
      m_DateLastUpdate(0,0,0)
{}

God::~God()
{}

void God::createWorld(descriptor::Galaxy* descriptor)
{
    assert(false);
//    m_galaxy = core::global::get().galaxyBuilder().create(descriptor);
//    __createLife(m_galaxy, descriptor);
//    if (descriptor.allow_invasion == true) {
//        __createInvasion(m_galaxy, descriptor);
//    }

//    bool player2space = true;
//    model::Starsystem* const starsystem = m_galaxy->randomSector()->randomStarsystem();
//    if (player2space == true) {
//        glm::vec3 center(500, 500, DEFAULT_ENTITY_ZPOS);
//        glm::vec3 angle(0,0,0);
//        //starsystem->AddVehicle(player->GetNpc()->vehicle(), center, angle, nullptr);
//    } else {
//        //starsystem->GetRandomPlanet()->GetLand()->AddVehicle(player->GetNpc()->vehicle());
//    }

//    __createShips(starsystem, /*ships_num=*/20, race::type::R0);   // fake
}

void God::update()
{
    // shortcuts
    TurnTimer& turnTimer = core::global::get().turnTimer();
    GameDate& gameDate = core::global::get().gameDate();
    // shortcuts

    turnTimer.update(-100);
    m_galaxy->update(turnTimer.getStopTurnTimer());

    if (m_DateLastUpdate - gameDate >= GOD_REST_IN_DAYS) {
        LOG("God::Update");

        m_galaxy->analizeStarSystemsCondition(data_starsystems_condition);
        m_DateLastUpdate = gameDate;

        //__proceedInvasion(galaxy);

        LOG(data_starsystems_condition.info());
    }

    if (turnTimer.getTurnEnded() == true) {
        turnTimer.nextTurn();
        gameDate.dayPass();
    }

    if (turnTimer.getTurnEnded() == true) {
        core::global::get().entityManager().clearGarbage();

        //            bool save_event = core::global::get().entityManager().UpdateSaveRequest();
        //            bool load_event = core::global::get().entityManager().UpdateLoadRequest();
        //            if (load_event == true) {
        //                player = core::global::get().entityManager().GetPlayer();
        //                galaxy = player->GetNpc()->vehicle()->starsystem()->GetSector()->GetGalaxy();
        //            }
        //            if (save_event == true) {
        //                //..
        //            }
    }

}

void God::__createLife(control::Galaxy* galaxy, descriptor::Galaxy* descriptor) const
{
    //    for(unsigned int i=0; i<galaxy->m_sectors.size(); i++) {
    //        for(unsigned int j=0; j<galaxy->m_sectors[i]->m_starsystems.size(); j++) {
    //            const StarSystemDescriptor& starsystem_descriptor = galaxy_descriptor.sector_descriptors[i].starsystem_descriptors[j];
    //            Starsystem* starsystem = galaxy->m_sectors[i]->m_starsystems[j];
    //            for(unsigned int j=0; j<starsystem->m_planets.size(); j++) {
    //                CreateLifeAtPlanet(starsystem->m_planets[j], starsystem_descriptor);
    //            }
    //            CreateSpaceStations(starsystem, starsystem_descriptor.spacestation_num);
    //        }
    //    }
}

void God::__createInvasion(control::Galaxy* galaxy, descriptor::Galaxy* descriptor) const
{
    assert(false);
//    for (unsigned int i=0; i<INITIATE_STARSYSTEM_IVASION_NUM; i++) {
//        Starsystem* starsystem = galaxy->randomSector()->randomStarsystem(ENTITY::STARSYSTEM::CONDITION::SAFE);
//        race::type race_id = (race::type)meti::getRandInt((int)race::type::R6, (int)race::type::R7);
//        int ship_num = meti::getRandInt(ENTITY::STARSYSTEM::SHIPENEMY_INIT_MIN, ENTITY::STARSYSTEM::SHIPENEMY_INIT_MAX);
//        __createShips(starsystem, ship_num, race_id);
//    }
}

void God::__proceedInvasion(control::Galaxy* galaxy) const
{
    assert(false);
//    std::cout<<"\nWARNING: God::ProceedInvasion is skiped\n";
//    return;

//    Starsystem* starsystem_invade_from = galaxy->randomSector()->randomStarsystem(ENTITY::STARSYSTEM::CONDITION::CAPTURED);
//    if (!starsystem_invade_from) {
//        return;
//    }
//    Starsystem* starsystem_invade_to = galaxy->closestSectorTo(starsystem_invade_from->sector())->closestStarsystemTo(starsystem_invade_from, ENTITY::STARSYSTEM::CONDITION::SAFE);
//    if (!starsystem_invade_to) {
//        return;
//    }
    
//    model::Npc* npc_leader = starsystem_invade_from->freeLeaderByRaceId(starsystem_invade_from->conquerorRaceId());
//    assert(npc_leader);
//    Task macrotask(type::AISCENARIO::MACRO_STARSYSTEMLIBERATION, starsystem_invade_to->id());
//    assert(false);
//    //npc_leader->stateMachine().setCurrentMacroTask(macrotask);
    
//    int num_max= 10;
//    starsystem_invade_from->createGroupAndShareTask(npc_leader, starsystem_invade_to, num_max);
}

void God::__createLifeAtPlanet(Planet* planet, const StarSystemDescriptor& starsystem_descriptor) const
{            
    //    unsigned long int population = 0;
    //    meti::getRandBool() ? population = meti::getRandInt(POPULATION_MIN, POPULATION_MAX) : population = 0;
    //    planet->SetPopulation(population);
    
    //    Land* land = nullptr;
    //    if (population > 0) { land = core::global::get().kosmoportBuilder().create(); }
    //    else                { land = core::global::get().natureLandBuilder().create(); }

    //    planet->BindLand(land);

    //    if (population > 0)
    //    {
    //        if (starsystem_descriptor.allow_satellites == true)
    //        {
    //            int sattelitewarriors_num = 1; //getRandInt(SATELLITEWARRIORS_PER_PLANET_MIN, SATELLITEWARRIORS_PER_PLANET_MAX);
    //            for (int j=0; j<sattelitewarriors_num; j++)
    //            {
    //                Satellite* satellite = core::global::get().satelliteBuilder().create();
    //               core::global::get().satelliteBuilder().equip(satellite); // improove

    //                {
    //                    race::type npc_race_id = meti::getRand(core::global::get().raceDescriptors().getRaces(type::KIND::GOOD));
    //                    entity::Type npc_subtype_id    = entity::Type::WARRIOR;
    //                    entity::Type npc_subsubtype_id = entity::Type::WARRIOR;

    //                    Npc* npc = core::global::get().npcBuilder().create(npc_race_id, npc_subtype_id, npc_subsubtype_id);
    //                    satellite->BindOwnerNpc(npc);
    //                }

    //                glm::vec3 orbit_center(0, 0, DEFAULT_ENTITY_ZPOS);
    //                glm::vec3 angle(0,0,0);
    //                planet->starsystem()->add(satellite, orbit_center, angle, planet);
    //            }
    //        }

    //        if (starsystem_descriptor.allow_ships == true)
    //        {
    //            std::vector<entity::Type> allowed_subtypes;
    //            if (starsystem_descriptor.allow_ship_ranger == true)      { allowed_subtypes.push_back(entity::Type::RANGER); }
    //            if (starsystem_descriptor.allow_ship_warrior == true)     { allowed_subtypes.push_back(entity::Type::WARRIOR); }
    //            if (starsystem_descriptor.allow_ship_trader == true)      { allowed_subtypes.push_back(entity::Type::TRADER); }
    //            if (starsystem_descriptor.allow_ship_pirat == true)       { allowed_subtypes.push_back(entity::Type::PIRAT); }
    //            if (starsystem_descriptor.allow_ship_diplomat == true)    { allowed_subtypes.push_back(entity::Type::DIPLOMAT); }

    //            int ship_num = meti::getRandInt(SHIPINIT_PER_PLANET_MIN, SHIPINIT_PER_PLANET_MAX);
    //            for (int j=0; j<ship_num; j++)
    //            {
    //                race::type npc_race_id = meti::getRand(core::global::get().raceDescriptors().getRaces(type::KIND::GOOD));
    //                entity::Type npc_subtype_id    = getRandNpcSubTypeId(npc_race_id, allowed_subtypes);
    //                entity::Type npc_subsubtype_id = getRandNpcSubSubTypeId(npc_subtype_id);

    //                Ship* new_ship = core::global::get().shipBuilder().create(descriptor::getNewVehicle());
    //               core::global::get().shipBuilder().equip(new_ship); // improove
    //                //ShipBuilder::Instance().EquipModules(ship, tech_level);
    //                //ShipBuilder::Instance().EquipArtefacts(ship, tech_level);
    //                //ShipBuilder::Instance().EquipBomb(ship, tech_level);

    //                Npc* new_npc = core::global::get().npcBuilder().create(npc_race_id, npc_subtype_id, npc_subsubtype_id);
    //                new_ship->BindOwnerNpc(new_npc);

    //                planet->AddVehicle(new_ship);
    //            }
    //        }
    //    }
}

void God::__createSpaceStations(Starsystem* starsystem, int spacestation_per_system) const
{       
    for (int i=0; i<spacestation_per_system; i++)
    {
        race::Type npc_race_id = meti::getRand(core::global::get().raceDescriptors().getRaces(race::KIND::GOOD));
        entity::Type npc_subtype_id    = entity::Type::WARRIOR;
        entity::Type npc_subsubtype_id = entity::Type::WARRIOR;

        //race::type ship_race_id = npc_race_id;         // RACES_ALL_vec[getRandInt(0, RACES_ALL_vec.size())];
        //entity::Type ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_vec[getRandInt(0, SHIP_SUBTYPE_vec.size())];
        //int weapons_num = 5;
        
        model::SpaceStation* spacestation = builder::SpaceStation::gen();
        assert(false);
        //core::global::get().spaceStationBuilder().equip(spacestation);  // improove

        model::Npc* npc = core::global::get().npcBuilder().create(npc_race_id, npc_subtype_id, npc_subsubtype_id);
        assert(false);
        //spacestation->bindNpc(npc);

        glm::vec2 center = meti::getRandVec2f(700, 1500);
        glm::vec3 center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
        //glm::vec3 angle(0,0,meti::getRandInt(360));

        assert(false);
//        starsystem->add(spacestation, center3/*, dir*/);
        
//        {
//            model::Satellite* satellite = core::global::get().satelliteBuilder().create();
//            assert(false);
//            //core::global::get().satelliteBuilder().equip(satellite);                   // improove

//            model::Npc* new_npc = core::global::get().npcBuilder().create(npc_race_id, npc_subtype_id, npc_subsubtype_id);
//            assert(false);
//            //satellite->bindNpc(new_npc);
            
//            glm::vec3 center(0.0f, 0.0f, DEFAULT_ENTITY_ZPOS);
//            glm::vec3 dir(0.0f, 1.0f, 0.0f);

//            starsystem->add(satellite, center, dir, spacestation);
//        }
    }
}

void God::__createShips(Starsystem* starsystem, int ship_num, race::Type npc_race_id, entity::Type subtype_id, entity::Type subsubtype_id) const
{
    entity::Type npc_subtype_id = entity::Type::NONE;
    entity::Type npc_subsubtype_id = entity::Type::NONE;

    for (int i=0; i<ship_num; i++)
    {
        // VERY UGLY LOGIC START (TODO)
        if (subtype_id == entity::Type::NONE) {
            npc_subtype_id    = getRandNpcSubTypeId(npc_race_id);
        } else {
            npc_subtype_id    = subtype_id;
        }

        if (subsubtype_id == entity::Type::NONE) {
            npc_subsubtype_id = getRandNpcSubSubTypeId(npc_subtype_id);
        } else {
            npc_subsubtype_id = subsubtype_id;
        }
        // VERY UGLY LOGIC END

        model::Ship* new_ship = builder::Ship::gen();
        assert(false);
        //builder::ShipBuilder::equip(new_ship); // improove

        model::Npc* new_npc = core::global::get().npcBuilder().create(npc_race_id, npc_subtype_id, npc_subsubtype_id);
        assert(false);
        //new_ship->bindNpc(new_npc);

        glm::vec3 center = meti::getRandXYVec3f(300, 1200, DEFAULT_ENTITY_ZPOS);
        //        glm::vec3 angle(0, 0, meti::getRandInt(360));
        assert(false);
//        starsystem->add(new_ship, center);
    }
}
